#pragma once

#include "util/Array2.hpp"
#include "FluidVariable.hpp"

template <size_t NX, size_t NY>
class FluidArray : public Array2<float, NX, NY> {
public:
    FluidArray<NX, NY>(FluidVariable var) : fluidVariable(var) {};
    const FluidVariable fluidVariable;
};

template <size_t NX, size_t NY>
void swap_fluid_array_data(FluidArray<NX, NY>& a, FluidArray<NX, NY>& b) {
    std::swap(a.mData, b.mData);
}
