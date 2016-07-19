#include <SFML/Graphics.hpp>
#include "SimpleFluid.hpp"
#include "input/InputHandler.hpp"

int main() {
    sf::SimpleFluid fluid;

    for (size_t i = 0; i < fluid.grid.xsize(); ++i) {
        for (size_t j = 0; j < fluid.grid.ysize(); ++j) {
            fluid.grid.density(i, j) = 1.0;

            if (i >     fluid.grid.xsize() / 4 &&
			    i < 3 * fluid.grid.xsize() / 4 &&
			    j >     fluid.grid.ysize() / 4 &&
			    j < 3 * fluid.grid.ysize() / 4) {
				fluid.grid.density(i, j) = 10.0;
            }
        }
    }

    InputHandler input_handler;

    unsigned int window_width = (unsigned int)std::ceil(sf::GRID_WIDTH * sf::PIXELS_PER_UNIT);
    unsigned int window_height = (unsigned int)std::ceil(sf::GRID_HEIGHT * sf::PIXELS_PER_UNIT);
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Simple Fluid");

    sf::Clock clock;

    while (window.isOpen()) {

        // Calculate time step
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        //Process input
        input_handler.process_input(window);

        // Update
        fluid.update(dt, input_handler.state);

        // Render
        window.clear();
        fluid.render(window);
        window.display();
    }
	return 0;
}
