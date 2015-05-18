#include "Grid.hpp"

Grid::Grid(const GridParameters &gp) :
	parameters(gp),
	density(parameters.ncells),
	velocity_x(parameters.ncells),
	velocity_y(parameters.ncells),
	temp_buffer_a(parameters.ncells),
	temp_buffer_b(parameters.ncells) {
}

size_t Grid::size(size_t dim) const {
	return parameters.ncells[dim];
}

void Grid::step(double dt) {
}
