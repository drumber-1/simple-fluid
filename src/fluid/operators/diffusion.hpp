#pragma once

#include "../common.hpp"

template <size_t NX, size_t NY>
void diffuse_simple(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, float diff, float dx, float dt) {

    float a = dt * diff / (dx * dx);

    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            output(i, j) = input(i, j);
            for (int n = 0; n < 4; ++n) {
                output(i, j) += a * input(i + IADJ[n], j + JADJ[n]);
            }
            output(i, j) -= 4.0f * a * input(i, j);
        }
    }
}

template <size_t NX, size_t NY>
void diffuse_gauss_seidel(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, float diff, float dx, float dt, size_t nsteps) {

    float a = dt * diff / (dx * dx);

    for (size_t istep = 0; istep < nsteps; ++istep) {
        for (size_t i = 1; i < NX - 1; ++i) {
            for (size_t j = 1; j < NY - 1; ++j) {
                output(i, j) = input(i, j) / (1 + (4 * a));
                for (size_t n = 0; n < 4; ++n) {
                    output(i, j) += a * output(i + IADJ[n], j + JADJ[n]) / (1.0f + (4.0f * a));
                }
            }
        }
    }
}