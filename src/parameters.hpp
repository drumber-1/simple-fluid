#pragma once

#include <string>

namespace simplefluid {
    const size_t GRID_XCELLS = 300;
    const size_t GRID_YCELLS = 300;
    const float GRID_WIDTH = 100.0f;
    const float GRID_HEIGHT = 100.0f;

    const float PIXELS_PER_UNIT = 5.0f;
    const float SCALE_RHO = 20.0f;
    const float SCALE_VELOCITY = 0.1f;

    const std::string COLOUR_MAP = "res/colourmap.png";
}