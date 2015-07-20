#pragma once

#include "../fluid/Grid.hpp"
#include "InputState.hpp"

template <size_t NX, size_t NY>
class FluidInteractor {
public:
    FluidInteractor(float pixels_per_unit, Grid<NX, NY>& grid);
    void update(float dt, InputState input_state, Grid<NX, NY>& grid);

private:
    const float pixels_per_cell_x;
    const float pixels_per_cell_y;

    const float FORCE = 50000.0f;
    const float SOURCE = 1000.0f; // Mass input, units: mass time^-1
    float mouse_last_x = 0.0f;
    float mouse_last_y = 0.0f;
};

template <size_t NX, size_t NY>
FluidInteractor<NX, NY>::FluidInteractor(float pixels_per_unit, Grid<NX, NY>& grid) : pixels_per_cell_x(pixels_per_unit * grid.units_per_cell_x),
                                                                              pixels_per_cell_y(pixels_per_unit * grid.units_per_cell_y) {
}


template <size_t NX, size_t NY>
void FluidInteractor<NX, NY>::update(float dt, InputState input_state, Grid<NX, NY>& grid) {
    size_t i = size_t(input_state.mouse_x / pixels_per_cell_x);
    size_t j = size_t(input_state.mouse_y / pixels_per_cell_y);

    if (input_state.add_density) {
        grid.source_density(i, j) += SOURCE / grid.cell_area();
    }

    if (input_state.add_velocity_start) {
        mouse_last_x = input_state.mouse_x;
        mouse_last_y = input_state.mouse_y;
    } else if (input_state.add_velocity) {
        grid.source_velocity_x(i, j) = FORCE * (input_state.mouse_x - mouse_last_x) / pixels_per_cell_x;
        grid.source_velocity_y(i, j) = FORCE * (input_state.mouse_y - mouse_last_y) / pixels_per_cell_x;
        mouse_last_x = input_state.mouse_x;
        mouse_last_y = input_state.mouse_y;
    }
}
