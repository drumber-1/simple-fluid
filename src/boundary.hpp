#pragma once

#include "util/Array2.hpp"
#include "FluidVariable.hpp"

template <size_t NX, size_t NY>
using FluidArray = Array2<double, NX, NY>;

template <size_t NX, size_t NY>
void set_bounds_wall(FluidVariable var, FluidArray<NX, NY> array) {
    for (size_t i = 1; i < NX - 1; ++i) {
        array(i, 0     ) = (var == FluidVariable::VELOCITY_Y) ? -array(i, 1     ) : array(i, 1     );
        array(i, NY - 1) = (var == FluidVariable::VELOCITY_Y) ? -array(i, NY - 2) : array(i, NY - 2);
    }
    for (size_t j = 1; j < NY - 1; ++j) {
        array(0     , j) = var == (FluidVariable::VELOCITY_X) ? -array(0     , j) : array(0     , j);
        array(NX - 1, j) = var == (FluidVariable::VELOCITY_X) ? -array(NX - 2, j) : array(NX - 2, j);
    }
    array(0     , 0     ) = 0.5 * (array(1     , 0     ) + array(0     , 1     ));
    array(0     , NY - 1) = 0.5 * (array(1     , NY - 1) + array(0     , NY - 2));
    array(NX - 1, 0     ) = 0.5 * (array(NX - 2, 0     ) + array(NX - 1, 1     ));
    array(NX - 1, NY - 1) = 0.5 * (array(NX - 2, NY - 1) + array(NX - 1, NY - 2));
}