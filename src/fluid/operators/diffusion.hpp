#pragma once

#include "../common.hpp"
#include "../boundary.hpp"

template <FluidVariable VAR, size_t NX, size_t NY>
void diffuse_simple(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, float diff, float dx, float dy, float dt, BoundaryType boundaryType) {

    float a = dt * diff / (dx * dy);

    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            output(i, j) = input(i, j) + a * (input(i + 1, j) + input(i - 1, j) + input(i, j + 1), + input(i, j - 1) + 4.0f * input(i, j));
        }
    }
    set_bounds<VAR>(output, boundaryType);
}

template <FluidVariable VAR, size_t NX, size_t NY>
void diffuse_gauss_seidel(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, float diff, float dx, float dy, float dt, size_t nsteps, BoundaryType boundaryType) {

    float a = dt * diff / (dx * dy);

    for (size_t istep = 0; istep < nsteps; ++istep) {
        for (size_t i = 1; i < NX - 1; ++i) {
            for (size_t j = 1; j < NY - 1; ++j) {
                output(i, j) = (input(i, j) + a * (output(i + 1, j) + output(i - 1, j), + output(i, j + 1), output(i, j - 1)))/ (1.0f + (4.0f * a));
            }
        }
    }
    set_bounds<VAR>(output, boundaryType);
}