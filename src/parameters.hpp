#pragma once

#include <string>

namespace simplefluid {
    const size_t NCELLS_X = 200;
    const size_t NCELLS_Y = 100;
    const float CELL_SPACING = 1.0f;

    const float PIXELS_PER_CELL = 5.0f;
    const float SCALE_RHO = 10.0f;
    const float SCALE_VELOCITY = 0.1f;

    const std::string COLOUR_MAP = "res/colourmap.png";
}