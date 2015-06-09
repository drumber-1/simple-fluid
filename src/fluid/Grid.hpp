#pragma once

#include <fstream>
#include <array>
#include <string>
#include <src/fluid/operators/projection.hpp>

#include "util/Array2.hpp"
#include "FluidVariable.hpp"
#include "boundary.hpp"
#include "operators/advection.hpp"


template <size_t NX, size_t NY>
class Grid {
public:
	Grid(double spacing);
	void step(double dt);
    void print_var(FluidVariable var, const std::string& postfix);
    double position(size_t index) const;
    double operator() (FluidVariable var, size_t i, size_t j) const;
    double& operator() (FluidVariable var, size_t i, size_t j);
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

    advect_linear_backtrace(mFluid[DENSITY], mFluid[BUFFER_A], mFluid[VELOCITY_X], mFluid[VELOCITY_Y], mSpacing, dt);
    std::swap(mFluid[DENSITY], mFluid[BUFFER_A]);
    set_bounds_wall(DENSITY, (mFluid[DENSITY]));

    project_hodge_decomp(mFluid[VELOCITY_X], mFluid[VELOCITY_Y], mFluid[BUFFER_A], mFluid[BUFFER_B], mSpacing, 20);
    set_bounds_wall(VELOCITY_X, (mFluid[VELOCITY_X]));
    set_bounds_wall(VELOCITY_Y, (mFluid[VELOCITY_Y]));

    advect_linear_backtrace(mFluid[VELOCITY_X], mFluid[BUFFER_A], mFluid[VELOCITY_X], mFluid[VELOCITY_Y], mSpacing, dt);
    std::swap(mFluid[VELOCITY_X], mFluid[BUFFER_A]);
    set_bounds_wall(VELOCITY_X, (mFluid[VELOCITY_X]));

    advect_linear_backtrace(mFluid[VELOCITY_Y], mFluid[BUFFER_A], mFluid[VELOCITY_X], mFluid[VELOCITY_Y], mSpacing, dt);
    std::swap(mFluid[VELOCITY_Y], mFluid[BUFFER_A]);
    set_bounds_wall(VELOCITY_Y, (mFluid[VELOCITY_Y]));

    project_hodge_decomp(mFluid[VELOCITY_X], mFluid[VELOCITY_Y], mFluid[BUFFER_A], mFluid[BUFFER_B], mSpacing, 20);
    set_bounds_wall(VELOCITY_X, (mFluid[VELOCITY_X]));
    set_bounds_wall(VELOCITY_Y, (mFluid[VELOCITY_Y]));

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
double Grid<NX, NY>::position(size_t index) const {
    return index * mSpacing;
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::initialise() {
    for (int i = 0; i < NX; ++i) {
        for (int j = 0; j < NY; ++j) {
            mFluid[DENSITY](i, j) = 1.0;
            mFluid[VELOCITY_X](i, j) = 0.0;
            mFluid[VELOCITY_Y](i, j) = 0.0;
            mFluid[BUFFER_A](i, j) = 0.0;
            mFluid[BUFFER_B](i, j) = 0.0;

            if (i > NX / 4 && i < 3 * NX / 4 && j > NY / 4 && j < 3 * NY / 4) {
                mFluid[VELOCITY_X](i, j) = 1.0;
                mFluid[DENSITY](i, j) = 10.0;
            }
        }
    }

    for (int n = 0; n < FluidVariable::NVAR; ++n) {
        FluidVariable var = static_cast<FluidVariable>(n);
        set_bounds_wall(var, mFluid[var]);
    }
}

template <size_t NX, size_t NY>
double Grid<NX, NY>::operator()(FluidVariable var, size_t i, size_t j) const {
    return mFluid[var](i, j);
}

template <size_t NX, size_t NY>
double& Grid<NX, NY>::operator()(FluidVariable var, size_t i, size_t j) {
    return mFluid[var](i, j);
}
