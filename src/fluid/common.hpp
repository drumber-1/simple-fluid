#pragma once

#include <array>
#include <functional>
#include "FluidArray.hpp"

template <size_t NX, size_t NY>
using BoundaryFunction = std::function<void(FluidArray<NX, NY>&)>;
