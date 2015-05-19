#pragma once

#include <fstream>
#include <array>
#include <string>

#include "util/Array2.hpp"
#include "FluidVariable.hpp"


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
};

template <size_t NX, size_t NY>
Grid<NX, NY>::Grid(double spacing) : mSpacing(spacing) {
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