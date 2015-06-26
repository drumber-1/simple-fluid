#include <iostream>

#include "fluid/Grid.hpp"
#include <SFML/Graphics.hpp>

const size_t GRIDX = 100;
const size_t GRIDY = 100;

const float RHOMAX = 10.0;
const float GRID_SCALE = 10.0f;

template <size_t NX, size_t NY>
void updateDensityVertices(const Grid<NX, NY> &grid, sf::VertexArray &vertices) {

    for (size_t i = 0; i < GRIDX; ++i) {
        for (size_t j = 0; j < GRIDY; ++j) {
            sf::Vertex* quad = &vertices[(i + j * GRIDX) * 4];

            int colx = (int)(256 * grid(FluidVariable::DENSITY, i, j) / RHOMAX);
            int coly = 0;

            quad[0].position = sf::Vector2f(GRID_SCALE * i      , GRID_SCALE * (j    ));
            quad[1].position = sf::Vector2f(GRID_SCALE * (i + 1), GRID_SCALE * (j    ));
            quad[2].position = sf::Vector2f(GRID_SCALE * (i + 1), GRID_SCALE * (j + 1));
            quad[3].position = sf::Vector2f(GRID_SCALE * (i    ), GRID_SCALE * (j + 1));

            for (int q = 0; q < 4; ++q) {
                quad[q].texCoords = sf::Vector2f(colx, coly);
            }
        }
    }
}

template <size_t NX, size_t NY>
void updateVelocityVertices(const Grid<NX, NY> &grid, sf::VertexArray &vertices) {
    float velocity_scaling = 1.0f;

    for (size_t i = 0; i < GRIDX; ++i) {
        for (size_t j = 0; j < GRIDY; ++j) {
            sf::Vertex* line = &vertices[(i + j * GRIDX) * 2];

            float xstart = GRID_SCALE * (i + 0.5f);
            float ystart = GRID_SCALE * (j + 0.5f);

            float xoffset = GRID_SCALE *  grid(FluidVariable::VELOCITY_X, i, j) * velocity_scaling;
            float yoffset = GRID_SCALE *  grid(FluidVariable::VELOCITY_Y, i, j) * velocity_scaling;

            line[0].position = sf::Vector2f(xstart, ystart);
            line[1].position = sf::Vector2f(xstart + xoffset, ystart + yoffset);

            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
        }
    }
}

int main() {

    const float spacing = 1.0;

	Grid<GRIDX, GRIDY> grid(spacing);

    sf::Texture colourMap;
    colourMap.loadFromFile("res/colourmap.png");
    std::cout << "Colour map loaded, (" << colourMap.getSize().x << ", " << colourMap.getSize().y << ")\n";

    sf::VertexArray densityVertices;
    densityVertices.setPrimitiveType(sf::Quads);
    densityVertices.resize(GRIDX * GRIDY * 4);
    updateDensityVertices(grid, densityVertices);

    sf::VertexArray velocityVertices;
    velocityVertices.setPrimitiveType(sf::Lines);
    velocityVertices.resize(GRIDX * GRIDY * 2);
    updateVelocityVertices(grid, velocityVertices);

    sf::RenderWindow window(sf::VideoMode(GRIDX * GRID_SCALE, GRIDY * GRID_SCALE), "SFML TEST");

    sf::Clock clock;
    bool fluidPaused = true;
    bool showVelocity = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::S) {
                    std::cout << "Updating grid" << "\n";
                    grid.step(0.4);
                    updateDensityVertices(grid, densityVertices);
                    if (showVelocity) {
                        updateVelocityVertices(grid, velocityVertices);
                    }
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
                    if (showVelocity) {
                        std::cout << "Velocity lines disabled\n";
                        showVelocity = false;
                    } else {
                        std::cout << "Velocity lines enabled\n";
                        showVelocity = true;
                    }
                }
            }
        }

        sf::Time elapsed = clock.restart();

        if (!fluidPaused) {
            grid.step(elapsed.asSeconds());
            updateDensityVertices(grid, densityVertices);
            if (showVelocity) {
                updateVelocityVertices(grid, velocityVertices);
            }
        }

        window.clear();
        window.draw(densityVertices, &colourMap);
        if (showVelocity) {
            window.draw(velocityVertices);
        }
        window.display();
    }


	return 0;
}
