#include "common.hpp"

void advect_linear_backtrace(const FluidArray& input, FluidArray& output, const FluidArray& xvel, const FluidArray& yvel, double dx, double dt);