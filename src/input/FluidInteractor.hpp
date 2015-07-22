#pragma once

#include "../fluid/Grid.hpp"
#include "InputState.hpp"

class DensityFunctor {
    const float SOURCE = 100.0f; // Mass input, units: mass time^-1
public:
    template <size_t NX, size_t NY>
    void operator()(Grid<NX, NY>& grid, size_t ncells, size_t i, size_t j) const {
        grid.source_density(i, j) += SOURCE / (ncells * grid.cell_area());
    }
};

class VelocityFunctor {
    const float FORCE = 50.0f;
public:
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    template <size_t NX, size_t NY>
    void operator()(Grid<NX, NY>& grid, size_t ncells, size_t i, size_t j) const {
        grid.source_velocity_x(i, j) += FORCE * velocity_x / grid.cell_area();
        grid.source_velocity_y(i, j) += FORCE * velocity_y / grid.cell_area();
    }
};

template <size_t NX, size_t NY>
class FluidInteractor {
public:
    FluidInteractor(float pixels_per_unit, Grid<NX, NY>& grid);
    void update(float dt, InputState input_state, Grid<NX, NY>& grid);

private:
    const float pixels_per_unit;

    DensityFunctor densityFunctor;
    VelocityFunctor velocityFunctor;

    float source_x = 0.0f;
    float source_y = 0.0f;

    float source_density_last_x = 0.0f;
    float source_density_last_y = 0.0f;
    float source_velocity_last_x = 0.0f;
    float source_velocity_last_y = 0.0f;
};

template <size_t NX, size_t NY>
FluidInteractor<NX, NY>::FluidInteractor(float pixels_per_unit, Grid<NX, NY>& grid) : pixels_per_unit(pixels_per_unit) {
}


template <size_t NX, size_t NY>
void FluidInteractor<NX, NY>::update(float dt, InputState input_state, Grid<NX, NY>& grid) {
    source_x = input_state.mouse_x / pixels_per_unit;
    source_y = input_state.mouse_y / pixels_per_unit;

    if (input_state.mouse_right_down_last) {
        source_density_last_x = source_x;
        source_density_last_y = source_y;
    } else if (input_state.mouse_right_down) {
        grid.apply_along_ray(densityFunctor, source_density_last_x, source_density_last_y, source_x, source_y);
        source_density_last_x = source_x;
        source_density_last_y = source_y;
    }

    if (input_state.mouse_left_down_last) {
        source_velocity_last_x = source_x;
        source_velocity_last_y = source_y;
    } else if (input_state.mouse_left_down) {
        velocityFunctor.velocity_x = (source_x - source_velocity_last_x) / dt;
        velocityFunctor.velocity_y = (source_y - source_velocity_last_y) / dt;
        grid.apply_along_ray(velocityFunctor, source_velocity_last_x, source_velocity_last_y, source_x, source_y);
        source_velocity_last_x = source_x;
        source_velocity_last_y = source_y;
    }
}
