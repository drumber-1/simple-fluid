#include "../src/fluid/Grid.hpp"
#include "../src/parameters.hpp"

const int NSTEPS = 100;
const float STEP_SIZE = 0.4f;

int main() {
	Grid<simplefluid::GRID_XCELLS, simplefluid::GRID_YCELLS> grid(simplefluid::GRID_WIDTH, simplefluid::GRID_HEIGHT, BoundaryType::WALL);

	for (int i = 0; i < NSTEPS; ++i) {
    	grid.step(STEP_SIZE);
    }

	return 0;
}
