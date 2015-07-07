#pragma once

#include "../fluid/Grid.hpp"
#include "InputState.hpp"
#include "../parameters.hpp"

template <size_t NX, size_t NY>
class FluidInteractor {
public:
    void update(float dt, InputState input_state, Grid<NX, NY>& grid);

private:
    const float FORCE = 50000.0f;
    const float SOURCE = 1000.0f; // Mass input, units: mass time^-1
    float mouse_last_x = 0.0f;
    float mouse_last_y = 0.0f;
};

template <size_t NX, size_t NY>
void FluidInteractor<NX, NY>::update(float dt, InputState input_state, Grid<NX, NY>& grid) {
    size_t i = size_t(input_state.mouse_x / simplefluid::PIXELS_PER_CELL);
    size_t j = size_t(input_state.mouse_y / simplefluid::PIXELS_PER_CELL);

    if (input_state.add_density) {
        grid.source_density(i, j) += SOURCE / (grid.get_spacing() * grid.get_spacing());
    }

    if (input_state.add_velocity_start) {
        mouse_last_x = input_state.mouse_x;
        mouse_last_y = input_state.mouse_y;
    } else if (input_state.add_velocity) {
        grid.source_velocity_x(i, j) = FORCE * (input_state.mouse_x - mouse_last_x) / simplefluid::PIXELS_PER_CELL;
        grid.source_velocity_y(i, j) = FORCE * (input_state.mouse_y - mouse_last_y) / simplefluid::PIXELS_PER_CELL;
        mouse_last_x = input_state.mouse_x;
        mouse_last_y = input_state.mouse_y;
    }
}
