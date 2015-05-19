#include <iostream>

#include "fluid/Grid.hpp"

std::string int_to_string(int n, int width);

int main() {

	Grid<100, 100> grid(1.0);

    grid.print_var(FluidVariable::DENSITY, "start");
    grid.print_var(FluidVariable::VELOCITY_X, "start");

    for (int n = 0; n < 10; ++n) {
        std::cout << "Calculating step: " << n << "\n";
        grid.step(1.0);

    }

    grid.print_var(FluidVariable::DENSITY, "end");
    grid.print_var(FluidVariable::VELOCITY_X, "end");


	return 0;
}
