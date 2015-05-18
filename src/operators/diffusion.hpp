#pragma once

#include "common.hpp"

void diffuse_simple(const FluidArray& input, FluidArray& output, double diff, double dx, double dt);
void diffuse_gauss_seidel(const FluidArray& input, FluidArray& output, double diff, double dx, double dt, size_t nsteps);