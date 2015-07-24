#pragma once

#include <fstream>
#include <array>
#include <string>
#include <cmath>
#include <limits>

#include "boundary.hpp"
#include "operators/advection.hpp"
#include "operators/projection.hpp"
#include "operators/misc.hpp"

template <size_t NX, size_t NY>
class Grid {
public:
	Grid(float size_x, float size_y, BoundaryType boundaryType);
	void step(float dt);
    float cell_area() const;
	inline bool in_grid(int i, int j) const;

    template<typename F>
    void apply_along_ray(F function, float x0, float y0, float x1, float y1);

    // Fluid Variables
    FluidArray<NX, NY> density;
    FluidArray<NX, NY> velocity_x;
    FluidArray<NX, NY> velocity_y;

    // Sources arrays
    FluidArray<NX, NY> source_density;
    FluidArray<NX, NY> source_velocity_x;
    FluidArray<NX, NY> source_velocity_y;

    // Buffer arrays
    FluidArray<NX, NY> buffer_a;
    FluidArray<NX, NY> buffer_b;

    const float units_x;
    const float units_y;
    const float units_per_cell_x;
    const float units_per_cell_y;
private:
    const BoundaryType boundType;

    void initialise();
    void set_boundaries();
};

template <size_t NX, size_t NY>
Grid<NX, NY>::Grid(float size_x, float size_y, BoundaryType boundaryType) : units_x(size_x), units_y(size_y),
                                                                            units_per_cell_x(size_x / NX), units_per_cell_y(size_y / NY),
                                                                            boundType(boundaryType) {
    initialise();
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::step(float dt) {
    add_source(source_density, density, dt);
    zero_array(source_density);
    advect_linear_backtrace<FluidVariable::DENSITY>(density, buffer_a, velocity_x, velocity_y, units_per_cell_x, units_per_cell_y, dt, boundType);
    std::swap(density, buffer_a);
    project_hodge_decomp(velocity_x, velocity_y, buffer_a, buffer_b, units_per_cell_x, units_per_cell_y, 20, boundType);

    add_source(source_velocity_x, velocity_x, dt);
    zero_array(source_velocity_x);
    advect_linear_backtrace<FluidVariable::VELOCITY_X>(velocity_x, buffer_a, velocity_x, velocity_y, units_per_cell_x, units_per_cell_y, dt, boundType);
    std::swap(velocity_x, buffer_a);

    add_source(source_velocity_y, velocity_y, dt);
    zero_array(source_velocity_y);
    advect_linear_backtrace<FluidVariable::VELOCITY_Y>(velocity_y, buffer_a, velocity_x, velocity_y, units_per_cell_x, units_per_cell_y, dt, boundType);
    std::swap(velocity_y, buffer_a);

    project_hodge_decomp(velocity_x, velocity_y, buffer_a, buffer_b, units_per_cell_x, units_per_cell_y, 20, boundType);
}

template <size_t NX, size_t NY>
float Grid<NX, NY>::cell_area() const {
    return units_per_cell_x * units_per_cell_y;
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::initialise() {

    zero_array(velocity_x);
    zero_array(velocity_y);

    zero_array(source_density);
    zero_array(source_velocity_x);
    zero_array(source_velocity_y);

    zero_array(buffer_a);
    zero_array(buffer_b);

    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            density(i, j) = 1.0;

            if (i > NX / 4 && i < 3 * NX / 4 && j > NY / 4 && j < 3 * NY / 4) {
                density(i, j) = 10.0;
            }
        }
    }

    set_boundaries();
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::set_boundaries() {
    set_bounds<FluidVariable::DENSITY>(density, boundType);
    set_bounds<FluidVariable::DENSITY>(velocity_x, boundType);
    set_bounds<FluidVariable::DENSITY>(velocity_y, boundType);
}

template <size_t NX, size_t NY>
inline bool Grid<NX, NY>::in_grid(int i, int j) const {
	//All arrays are the same size
	return density.in_grid(i, j);
}

template <size_t NX, size_t NY>
template <typename F>
void Grid<NX, NY>::apply_along_ray(F function, float x0, float y0, float x1, float y1) {

    //First convert x and y from units to cells
    x0 /= units_per_cell_x;
    x1 /= units_per_cell_x;
    y0 /= units_per_cell_y;
    y1 /= units_per_cell_y;

    float dx = std::abs(x1 - x0);
    float dy = std::abs(y1 - y0);

    int i = (int) std::floor(x0);
    int j = (int) std::floor(y0);

    int i1 = (int) std::floor(x1);
    int j1 = (int) std::floor(y1);

    size_t n = 1;
    float error = 0.0f;
    int dir_x, dir_y;

    if (dx == 0) {
        dir_x = 0;
        error = std::numeric_limits<float>::infinity();
    } else if (x1 > x0) {
        dir_x = 1;
        n += i1 - i;
        error = (i + 1 - x0) * dy;
    } else {
        dir_x = -1;
        n += i - i1;
        error = (x0 - i) * dy;
    }

    if (dy == 0) {
        dir_y = 0;
        error -= std::numeric_limits<float>::infinity();
    } else if (y1 > y0) {
        dir_y = 1;
        n += j1 - j;
        error -= (j + 1 - y0) * dx;
    } else {
        dir_y = -1;
        n += j - j1;
        error -= (y0 - j) * dx;
    }

    for (size_t icell = 0; icell < n; ++icell) {
		if (in_grid(i, j)) {
			function(*this, n, i, j);
		}

        if (error > 0) {
            j += dir_y;
            error -= dx;
        } else {
            i += dir_x;
            error += dy;
        }
    }
}
