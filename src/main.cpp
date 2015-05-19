#include <iostream>
#include "Grid.hpp"

int main() {

	Grid<100, 100> grid(1.0);
    grid.print_var(FluidVariable::DENSITY, "");
    grid.print_var(FluidVariable::VELOCITY_X, "");

	return 0;
}