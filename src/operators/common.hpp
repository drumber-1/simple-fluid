#pragma once

#include <array>
#include "../util/Array2.hpp"

using FluidArray = Array2<double>;

//i and j adjacency arrays, for convenience in loops
const std::array<int, 4> IADJ = {{-1, +1, 0, 0}};
const std::array<int, 4> JADJ = {{0, 0, -1, +1}};
