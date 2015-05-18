#include <iostream>
#include <fstream>
#include <cmath>

#include "grid/Grid.hpp"

int main() {

	GridParameters gp;
	gp.ncells = {{10, 10}};
	gp.spacing = 1;
	
	Grid grid(gp);

	/*for (size_t i = 0; i < grid.size(0); ++i) {
		for (size_t j = 0; j < grid.size(1); ++j) {
			double x = grid.get_position(i, 0);
			double y = grid.get_position(j, 1);

			if (std::abs(x) < 70 && std::abs(y) < 50) {
				grid({{i, j}}).velocity = {{10, 0}};
			} else {
				grid({{i, j}}).velocity = {{0, 0}};
			}
		}
	}

	std::ofstream fout("grid.out");
	grid.print(fout);*/

	return 0;
}