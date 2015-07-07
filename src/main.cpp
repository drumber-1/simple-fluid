#include <iostream>

#include <SFML/Graphics.hpp>
#include "fluid/Grid.hpp"
#include "graphics/GridRenderer.hpp"

const size_t GRIDX = 200;
const size_t GRIDY = 100;

const float PIXELS_PER_CELL = 5.0f;

const float SCALE_RHO = 10.0;
const float SCALE_VELOCITY = 0.1f;

int main() {
    const float spacing = 1.0;
    const float force = 50000.0f;
    const float source = 1000.0f;

	Grid<GRIDX, GRIDY> grid(spacing);

    GridRenderer<GRIDX, GRIDY> grid_renderer("res/colourmap.png", PIXELS_PER_CELL, SCALE_RHO, SCALE_VELOCITY);
    grid_renderer.initialiseVertices(grid);

    unsigned int window_width = std::ceil(GRIDX * PIXELS_PER_CELL);
    unsigned int window_height = std::ceil(GRIDY * PIXELS_PER_CELL);
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Simple Fluid");

    sf::Clock clock;
    bool fluidPaused = false;

    bool mouseleftdown = false;
    bool mouserightdown = false;
    int mousedownx = 0;
    int mousedowny = 0;
    int mousex = 0;
    int mousey = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S && fluidPaused) {
                    std::cout << "Updating grid" << "\n";
                    grid.step(0.4);
                    grid_renderer.updateVertices(grid);
                } else if (event.key.code == sf::Keyboard::Space) {
                    if (fluidPaused) {
                        std::cout << "Fluid unpaused\n";
                        fluidPaused = false;
                        clock.restart();
                    } else {
                        std::cout << "Fluid paused\n";
                        fluidPaused = true;
                    }
                } else if (event.key.code == sf::Keyboard::V) {
                    if (grid_renderer.draw_velocity) {
                        std::cout << "Velocity lines disabled\n";
                        grid_renderer.draw_velocity = false;
                    } else {
                        std::cout << "Velocity lines enabled\n";
                        grid_renderer.draw_velocity = true;
                    }
                } else if (event.key.code == sf::Keyboard::G) {
                    if (grid_renderer.draw_grid) {
                        std::cout << "Grid lines disabled\n";
                        grid_renderer.draw_grid = false;
                    } else {
                        std::cout << "Grid lines enabled\n";
                        grid_renderer.draw_grid = true;
                    }
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                mousedownx = event.mouseButton.x;
                mousedowny = event.mouseButton.y;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseleftdown = true;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    mouserightdown = true;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseleftdown = false;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    mouserightdown = false;
                }
            } else if (event.type == sf::Event::MouseMoved) {
                mousex = event.mouseMove.x;
                mousey = event.mouseMove.y;
            }
        }

        sf::Time elapsed = clock.restart();

        if (!fluidPaused) {
            size_t i = size_t(mousex / PIXELS_PER_CELL);
            size_t j = size_t(mousey / PIXELS_PER_CELL);

            if (mouseleftdown) {
                grid.source_velocity_x(i, j) = force * (mousex - mousedownx) / PIXELS_PER_CELL;
                grid.source_velocity_y(i, j) = force * (mousey - mousedowny) / PIXELS_PER_CELL;
                mousedownx = mousex;
                mousedowny = mousey;
            }
            if (mouserightdown) {
                grid.source_density(i, j) += source;
            }

            float dt = elapsed.asSeconds();
            grid.step(dt);
            grid_renderer.updateVertices(grid);
        }

        window.clear();
        grid_renderer.render(window);
        window.display();
    }

	return 0;
}
