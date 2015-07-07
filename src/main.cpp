#include <SFML/Graphics.hpp>
#include "SimpleFluid.hpp"
#include "input/InputHandler.hpp"

int main() {
    simplefluid::SimpleFluid fluid;
    InputHandler input_handler;

    unsigned int window_width = std::ceil(simplefluid::NCELLS_X * simplefluid::PIXELS_PER_CELL);
    unsigned int window_height = std::ceil(simplefluid::NCELLS_Y * simplefluid::PIXELS_PER_CELL);
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
