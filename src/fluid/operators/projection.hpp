#pragma once

#include "../common.hpp"

template <size_t NX, size_t NY>
void project_hodge_decomp(FluidArray<NX, NY>& xvel, FluidArray<NX, NY>& yvel, FluidArray<NX, NY>& p, FluidArray<NX, NY>& div, float dx, size_t nsteps, BoundaryFunction<NX, NY> boundary) {
    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            div(i, j) = -0.5f * dx * (xvel(i + 1, j) - xvel(i - 1, j) + yvel(i, j + 1) - yvel(i, j - 1));
            p(i, j) = 0.0;
        }
    }

    boundary(div);
    boundary(p);

    for (size_t istep = 0; istep < nsteps; ++istep) {
        for (size_t i = 1; i < NX - 1; ++i) {
            for (size_t j = 1; j < NY - 1; ++j) {
                p(i, j) = (div(i, j) + p(i + 1, j) + p(i - 1, j) + p(i, j + 1) + p(i, j - 1)) / 4.0f;
            }
        }
        boundary(p);
    }

    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            xvel(i, j) -= 0.5 * (p(i + 1, j) - p(i - 1, j)) / dx;
            yvel(i, j) -= 0.5 * (p(i, j + 1) - p(i, j - 1)) / dx;
        }
    }

    boundary(xvel);
    boundary(yvel);
}
