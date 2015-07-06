#pragma once

#include <fstream>
#include <array>
#include <string>

#include "boundary.hpp"
#include "operators/advection.hpp"
#include "operators/projection.hpp"
#include "operators/misc.hpp"

template <size_t NX, size_t NY>
class Grid {
public:
	Grid(float spacing);
	void step(float dt);
    float position(size_t index) const;

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
private:
	const float mSpacing;
    BoundaryFunction<NX, NY> bf;

    void initialise();
    void set_boundaries();
};

template <size_t NX, size_t NY>
Grid<NX, NY>::Grid(float spacing) : mSpacing(spacing) {
    bf = set_bounds_wall<NX, NY>;
    initialise();
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::step(float dt) {
    add_source(source_density, density, dt);
    zero_array(source_density);
    advect_linear_backtrace(density, buffer_a, velocity_x, velocity_y, mSpacing, dt, bf, FluidVariable::DENSITY);
    std::swap(density, buffer_a);
    project_hodge_decomp(velocity_x, velocity_y, buffer_a, buffer_b, mSpacing, 20, bf);

    add_source(source_velocity_x, velocity_x, dt);
    zero_array(source_velocity_x);
    advect_linear_backtrace(velocity_x, buffer_a, velocity_x, velocity_y, mSpacing, dt, bf, FluidVariable::VELOCITY_X);
    std::swap(velocity_x, buffer_a);

    add_source(source_velocity_y, velocity_y, dt);
    zero_array(source_velocity_y);
    advect_linear_backtrace(velocity_y, buffer_a, velocity_x, velocity_y, mSpacing, dt, bf, FluidVariable::VELOCITY_Y);
    std::swap(velocity_y, buffer_a);

    project_hodge_decomp(velocity_x, velocity_y, buffer_a, buffer_b, mSpacing, 20, bf);
}

template <size_t NX, size_t NY>
float Grid<NX, NY>::position(size_t index) const {
    return index * mSpacing;
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
    set_bounds_wall<NX, NY>(density, FluidVariable::DENSITY);
    set_bounds_wall<NX, NY>(velocity_x, FluidVariable::VELOCITY_X);
    set_bounds_wall<NX, NY>(velocity_y, FluidVariable::VELOCITY_Y);
}
