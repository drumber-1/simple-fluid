#pragma once

#include <functional>
#include "util/Array2.hpp"
#include "FluidVariable.hpp"

template <size_t NX, size_t NY>
using FluidArray = Array2<float, NX, NY>;

template <size_t NX, size_t NY>
using BoundaryFunction = std::function<void(FluidArray<NX, NY>&, FluidVariable)>;
