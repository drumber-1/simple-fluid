#pragma once

#include <src/fluid/common.hpp>

template <size_t NX, size_t NY>
void add_source(const FluidArray<NX, NY>& source, FluidArray<NX, NY>& target, float dt) {
    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            target(i, j) += source(i, j) * dt;
        }
    }
}

template <size_t NX, size_t NY>
void zero_array(FluidArray<NX, NY>& array) {
    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            array(i, j) = 0.0f;
        }
    }
}