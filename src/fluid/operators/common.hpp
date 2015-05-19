#pragma once

#include <array>
#include "../util/Array2.hpp"

template <size_t NX, size_t NY>
using FluidArray = Array2<double, NX, NY>;

//i and j adjacency arrays, for convenience in loops
const std::array<int, 4> IADJ = {{-1, +1, 0, 0}};
const std::array<int, 4> JADJ = {{0, 0, -1, +1}};
