#pragma once

#include <fstream>
#include <array>
#include <string>

#include "util/Array2.hpp"
#include "FluidVariable.hpp"
#include "boundary.hpp"


template <size_t NX, size_t NY>
class Grid {
public:
	Grid(double spacing);
	void step(double dt);
    void print_var(FluidVariable var, const std::string& postfix);
private:
    using FluidArray = Array2<double, NX, NY>;

	const double mSpacing;
	std::array<FluidArray, FluidVariable::NVAR> mFluid;

    void initialise();
};

template <size_t NX, size_t NY>
Grid<NX, NY>::Grid(double spacing) : mSpacing(spacing) {
    initialise();
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::step(double dt) {
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::print_var(FluidVariable var, const std::string& postfix) {
    std::string fname = VARNAMES[var];
    if (postfix != "") {
        fname += "_" + postfix;
    }
    fname += ".txt";
    std::ofstream out(fname.c_str());
    out <<"X\tY\t" << VARNAMES[var] << "\n";
    for (int i = 0; i < NX; ++i) {
        for (int j = 0; j < NY; ++j) {
            out << i * mSpacing << "\t" << j * mSpacing << "\t" << mFluid[var](i, j) << "\n";
        }
    }
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::initialise() {
    for (int i = 0; i < NX; ++i) {
        for (int j = 0; j < NY; ++j) {
            mFluid[FluidVariable::DENSITY](i, j) = 1.0;
            mFluid[FluidVariable::VELOCITY_X](i, j) = 1.0;
            mFluid[FluidVariable::VELOCITY_Y](i, j) = 0.0;
            mFluid[FluidVariable::BUFFER_A](i, j) = 0.0;
            mFluid[FluidVariable::BUFFER_B](i, j) = 0.0;

            if (i > NX / 4 && i < 3 * NX / 4 && j > NY / 4 && j < 3 * NY / 4) {
                mFluid[FluidVariable::DENSITY](i, j) = 10.0;
            }
        }
    }

    for (int n = 0; n < FluidVariable::NVAR; ++n) {
        FluidVariable var = static_cast<FluidVariable>(n);
        set_bounds_wall(var, mFluid[var]);
    }
}
