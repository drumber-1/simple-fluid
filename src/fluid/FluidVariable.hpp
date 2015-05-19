#pragma once

#include <array>

enum FluidVariable {
    DENSITY,
    VELOCITY_X,
    VELOCITY_Y,
    BUFFER_A,
    BUFFER_B,
    NVAR
};

const std::array<std::string, NVAR> VARNAMES =
        {"density",
        "velocity_x",
        "velocity_y",
        "buff_a",
        "buff_b"};
