#pragma once

#include <array>

#include "../util/Array2.hpp"

enum FluidVariable {
	DENSITY,
	VELOCITYX,
	VELOCITYY,
	BUFFER_A,
	BUFFER_B,
	NVAR
};

template <size_t NX, size_t NY>
class Grid {
public:
	Grid(double spacing);
	void step(double dt);
private:
    using FluidArray = Array2<double, NX, NY>;

	const double mSpacing;
	std::array<FluidArray, NVAR> mFluid;
};

template <size_t NX, size_t NY>
Grid<NX, NY>::Grid(double spacing) : mSpacing(spacing) {
}

template <size_t NX, size_t NY>
void Grid<NX, NY>::step(double dt) {
}