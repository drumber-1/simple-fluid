#pragma once

#include "common.hpp"
#include "FluidVariable.hpp"

enum BoundaryType {
    WALL,
    FREE,
    INFLOW,
    OUTFLOW
};

template <FluidVariable VAR, size_t NX, size_t NY>
void set_bounds_wall(FluidArray<NX, NY>& array);

template <size_t NX, size_t NY>
void set_bounds_free(FluidArray<NX, NY>& array);

template <FluidVariable VAR, size_t NX, size_t NY>
void set_bounds_inflow(FluidArray<NX, NY>& array);

template <FluidVariable VAR, size_t NX, size_t NY>
void set_bounds_outflow(FluidArray<NX, NY>& array);

template<FluidVariable VAR, size_t NX, size_t NY>
void set_bounds(FluidArray<NX, NY>& array, BoundaryType bt) {
    switch (bt) {
        case WALL:
            set_bounds_wall<VAR>(array);
            break;
        case FREE:
            set_bounds_free(array);
            break;
		case INFLOW:
			set_bounds_inflow<VAR>(array);
			break;
		case OUTFLOW:
			set_bounds_outflow<VAR>(array);
			break;
    }
}

template <FluidVariable VAR, size_t NX, size_t NY>
void set_bounds_wall(FluidArray<NX, NY>& array) {
    switch (VAR) {
        case FluidVariable::VELOCITY_X:
            for (size_t i = 1; i < NX - 1; ++i) {
                array(i, 0     ) = array(i, 1     );
                array(i, NY - 1) = array(i, NY - 2);
            }
            for (size_t j = 1; j < NY - 1; ++j) {
                array(0     , j) = -array(1     , j);
                array(NX - 1, j) = -array(NX - 2, j);
            }
            break;
        case FluidVariable::VELOCITY_Y:
            for (size_t i = 1; i < NX - 1; ++i) {
                array(i, 0     ) = -array(i, 1     );
                array(i, NY - 1) = -array(i, NY - 2);
            }
            for (size_t j = 1; j < NY - 1; ++j) {
                array(0     , j) = array(1     , j);
                array(NX - 1, j) = array(NX - 2, j);
            }
            break;
        default:
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

template <size_t NX, size_t NY>
void set_bounds_free(FluidArray<NX, NY>& array) {
    for (size_t i = 1; i < NX - 1; ++i) {
        array(i, 0     ) = array(i, 1     );
        array(i, NY - 1) = array(i, NY - 2);
    }
    for (size_t j = 1; j < NY - 1; ++j) {
        array(0     , j) = array(1     , j);
        array(NX - 1, j) = array(NX - 2, j);
    }
    array(0     , 0     ) = 0.5f * (array(1     , 0     ) + array(0     , 1     ));
    array(0     , NY - 1) = 0.5f * (array(1     , NY - 1) + array(0     , NY - 2));
    array(NX - 1, 0     ) = 0.5f * (array(NX - 2, 0     ) + array(NX - 1, 1     ));
    array(NX - 1, NY - 1) = 0.5f * (array(NX - 2, NY - 1) + array(NX - 1, NY - 2));
}

template <FluidVariable VAR, size_t NX, size_t NY>
void set_bounds_inflow(FluidArray<NX, NY>& array) {
	switch (VAR) {
		case FluidVariable::VELOCITY_X:
			for (size_t i = 1; i < NX - 1; ++i) {
				array(i, 0     ) = array(i, 1     );
				array(i, NY - 1) = array(i, NY - 2);
			}
			for (size_t j = 1; j < NY - 1; ++j) {
				array(0     , j) =      std::abs(array(1     , j));
				array(NX - 1, j) = -1 * std::abs(array(NX - 2, j));
			}
			break;
		case FluidVariable::VELOCITY_Y:
			for (size_t i = 1; i < NX - 1; ++i) {
				array(i, 0     ) =      std::abs(array(i, 1     ));
				array(i, NY - 1) = -1 * std::abs(array(i, NY - 2));
			}
			for (size_t j = 1; j < NY - 1; ++j) {
				array(0     , j) = array(1     , j);
				array(NX - 1, j) = array(NX - 2, j);
			}
			break;
		default:
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

template <FluidVariable VAR, size_t NX, size_t NY>
void set_bounds_outflow(FluidArray<NX, NY>& array)  {
	switch (VAR) {
		case FluidVariable::VELOCITY_X:
			for (size_t i = 1; i < NX - 1; ++i) {
				array(i, 0     ) = array(i, 1     );
				array(i, NY - 1) = array(i, NY - 2);
			}
			for (size_t j = 1; j < NY - 1; ++j) {
				array(0     , j) = -1 * std::abs(array(1     , j));
				array(NX - 1, j) =      std::abs(array(NX - 2, j));
			}
			break;
		case FluidVariable::VELOCITY_Y:
			for (size_t i = 1; i < NX - 1; ++i) {
				array(i, 0     ) = -1 * std::abs(array(i, 1     ));
				array(i, NY - 1) =      std::abs(array(i, NY - 2));
			}
			for (size_t j = 1; j < NY - 1; ++j) {
				array(0     , j) = array(1     , j);
				array(NX - 1, j) = array(NX - 2, j);
			}
			break;
		default:
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