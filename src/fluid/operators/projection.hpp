#pragma once

#include "../common.hpp"
#include "../boundary.hpp"

template <size_t NX, size_t NY>
void project_hodge_decomp(FluidArray<NX, NY>& xvel, FluidArray<NX, NY>& yvel, FluidArray<NX, NY>& p, FluidArray<NX, NY>& div, float dx, float dy, size_t nsteps, BoundaryType boundaryType) {
    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            div(i, j) = -0.5f * (dx * (xvel(i + 1, j) - xvel(i - 1, j)) + (dy * (yvel(i, j + 1) - yvel(i, j - 1))));
            p(i, j) = 0.0;
        }
    }

    set_bounds<FluidVariable::OTHER>(div, boundaryType);
    set_bounds<FluidVariable::OTHER>(p, boundaryType);

    for (size_t istep = 0; istep < nsteps; ++istep) {
        for (size_t i = 1; i < NX - 1; ++i) {
            for (size_t j = 1; j < NY - 1; ++j) {
                p(i, j) = (div(i, j) + p(i + 1, j) + p(i - 1, j) + p(i, j + 1) + p(i, j - 1)) / 4.0f;
            }
        }
        //set_bounds<FluidVariable::OTHER, NX, NY>(p, boundaryType);
    }

    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            xvel(i, j) -= 0.5 * (p(i + 1, j) - p(i - 1, j)) / dx;
            yvel(i, j) -= 0.5 * (p(i, j + 1) - p(i, j - 1)) / dy;
        }
    }

    set_bounds<FluidVariable::VELOCITY_X>(xvel, boundaryType);
    set_bounds<FluidVariable::VELOCITY_Y>(yvel, boundaryType);
}
