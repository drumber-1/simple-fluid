#pragma once

#include "common.hpp"

template <size_t NX, size_t NY>
void diffuse_simple(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, double diff, double dx, double dt) {

    double a = dt * diff / (dx * dx);

    for (int i = 1; i < NX - 1; ++i) {
        for (int j = 1; j < NY - 1; ++j) {
            output(i, j) = input(i, j);
            for (int n = 0; n < 4; ++n) {
                output(i, j) += a * input(i + IADJ[n], j + JADJ[n]);
            }
            output(i, j) -= 4.0 * a * input(i, j);
        }
    }
}

template <size_t NX, size_t NY>
void diffuse_gauss_seidel(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, double diff, double dx, double dt, size_t nsteps) {

    double a = dt * diff / (dx * dx);

    for (int istep = 0; istep < nsteps; ++istep) {
        for (int i = 1; i < NX - 1; ++i) {
            for (int j = 1; j < NY - 1; ++j) {
                output(i, j) = input(i, j) / (1 + (4 * a));
                for (int n = 0; n < 4; ++n) {
                    output(i, j) += a * output(i + IADJ[n], j + JADJ[n]) / (1.0 + (4.0 * a));
                }
            }
        }
    }
}