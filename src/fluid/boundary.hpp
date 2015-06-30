#pragma once

#include "common.hpp"
#include "FluidArray.hpp"
#include "FluidVariable.hpp"

template <size_t NX, size_t NY>
void set_bounds_wall(FluidArray<NX, NY>& array) {
    if (array.fluidVariable == FluidVariable::VELOCITY_X) {
        for (size_t i = 1; i < NX - 1; ++i) {
            array(i, 0     ) = array(i, 1     );
            array(i, NY - 1) = array(i, NY - 2);
        }
        for (size_t j = 1; j < NY - 1; ++j) {
            array(0     , j) = -array(1     , j);
            array(NX - 1, j) = -array(NX - 2, j);
        }
    } else if (array.fluidVariable == FluidVariable::VELOCITY_Y) {
        for (size_t i = 1; i < NX - 1; ++i) {
            array(i, 0     ) = -array(i, 1     );
            array(i, NY - 1) = -array(i, NY - 2);
        }
        for (size_t j = 1; j < NY - 1; ++j) {
            array(0     , j) = array(1     , j);
            array(NX - 1, j) = array(NX - 2, j);
        }
    } else {
        for (size_t i = 1; i < NX - 1; ++i) {
            array(i, 0     ) = array(i, 1     );
            array(i, NY - 1) = array(i, NY - 2);
        }
        for (size_t j = 1; j < NY - 1; ++j) {
            array(0     , j) = array(1     , j);
            array(NX - 1, j) = array(NX - 2, j);
        }
    }
    array(0     , 0     ) = 0.5f * (array(1     , 0     ) + array(0     , 1     ));
    array(0     , NY - 1) = 0.5f * (array(1     , NY - 1) + array(0     , NY - 2));
    array(NX - 1, 0     ) = 0.5f * (array(NX - 2, 0     ) + array(NX - 1, 1     ));
    array(NX - 1, NY - 1) = 0.5f * (array(NX - 2, NY - 1) + array(NX - 1, NY - 2));
}