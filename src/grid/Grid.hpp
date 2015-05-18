#pragma once

#include <array>

#include "../util/Array2.hpp"
#include "GridParameters.hpp"

using FluidArray = Array2<double>;

class Grid {
public:
	Grid(const GridParameters& gp);

	size_t size(size_t dim) const;
	void step(double dt);
private:
	const GridParameters parameters;

	FluidArray density;
	FluidArray velocity_x;
	FluidArray velocity_y;
	FluidArray temp_buffer_a;
	FluidArray temp_buffer_b;
};
