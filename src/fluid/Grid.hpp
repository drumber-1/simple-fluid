#pragma once

#include <fstream>
#include <array>
#include <string>

#include "FluidArray.hpp"
#include "FluidVariable.hpp"
#include "boundary.hpp"
#include "operators/advection.hpp"
#include "operators/projection.hpp"

template <size_t NX, size_t NY>
class Grid {
public:
	Grid(float spacing);
	void step(float dt);
    float position(size_t index) const;

    FluidArray<NX, NY> density;
    FluidArray<NX, NY> velocity_x;
    FluidArray<NX, NY> velocity_y;
    FluidArray<NX, NY> buffer_a;
    FluidArray<NX, NY> buffer_b;
private:
	const float mSpacing;
    BoundaryFunction<NX, NY> bf;

    void initialise();
    void set_boundaries();
};

template <size_t NX, size_t NY>
Grid<NX, NY>::Grid(float spacing) : density(FluidVariable::DENSITY),
                                    velocity_x(FluidVariable::VELOCITY_X),
                                    velocity_y(FluidVariable::VELOCITY_Y),
                                    buffer_a(FluidVariable::OTHER),
                                    buffer_b(FluidVariable::OTHER),
                                    mSpacing(spacing) {
    bf = set_bounds_wall<NX, NY>;
    initialise();
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::step(float dt) {
    advect_linear_backtrace(density, buffer_a, velocity_x, velocity_y, mSpacing, dt, bf);
    swap_fluid_array_data(density, buffer_a);
    project_hodge_decomp(velocity_x, velocity_y, buffer_a, buffer_b, mSpacing, 20, bf);

    advect_linear_backtrace(velocity_x, buffer_a, velocity_x, velocity_y, mSpacing, dt, bf);
    swap_fluid_array_data(velocity_x, buffer_a);

    advect_linear_backtrace(velocity_y, buffer_a, velocity_x, velocity_y, mSpacing, dt, bf);
    swap_fluid_array_data(velocity_y, buffer_a);

    project_hodge_decomp(velocity_x, velocity_y, buffer_a, buffer_b, mSpacing, 20, bf);
}

template <size_t NX, size_t NY>
float Grid<NX, NY>::position(size_t index) const {
    return index * mSpacing;
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::initialise() {
    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            density(i, j) = 1.0;
            velocity_x(i, j) = 0.0;
            velocity_y(i, j) = 0.0;
            buffer_a(i, j) = 0.0;
            buffer_b(i, j) = 0.0;

            if (i > NX / 4 && i < 3 * NX / 4 && j > NY / 4 && j < 3 * NY / 4) {
                velocity_x(i, j) = 1.0;
                density(i, j) = 10.0;
            }
        }
    }

    set_boundaries();
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::set_boundaries() {
    set_bounds_wall<NX, NY>(density);
    set_bounds_wall<NX, NY>(velocity_x);
    set_bounds_wall<NX, NY>(velocity_y);
}
