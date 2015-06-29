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

template <size_t NX, size_t NY>
void updateGridVertices(const Grid<NX, NY> &grid, sf::VertexArray &vertices) {
    for (size_t i = 0; i <= GRIDX; ++i) {
        sf::Vertex* line = &vertices[2 * i];

        line[0].position = sf::Vector2f(i * GRID_SCALE, 0);
        line[1].position = sf::Vector2f(i * GRID_SCALE, GRIDY * GRID_SCALE);

        line[0].color = sf::Color::Blue;
        line[1].color = sf::Color::Blue;
    }
    for (size_t j = 0; j <= GRIDY; ++j) {
        sf::Vertex* line = &vertices[2 * (GRIDX + 1 + j)];

        line[0].position = sf::Vector2f(0, j * GRID_SCALE);
        line[1].position = sf::Vector2f(GRIDX * GRID_SCALE, j * GRID_SCALE);

        line[0].color = sf::Color::Blue;
        line[1].color = sf::Color::Blue;
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

    sf::VertexArray gridVertices;
    gridVertices.setPrimitiveType(sf::Lines);
    gridVertices.resize(2 * (GRIDX + GRIDY + 2));
    updateGridVertices(grid, gridVertices);

    unsigned int window_width = std::ceil(GRIDX * GRID_SCALE);
    unsigned int window_height = std::ceil(GRIDY * GRID_SCALE);
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML TEST");

    sf::Clock clock;
    bool fluidPaused = true;
    bool showVelocity = false;
    bool showGrid = false;

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
                } else if (event.key.code == sf::Keyboard::G) {
                    if (showGrid) {
                        std::cout << "Grid lines disabled\n";
                        showGrid = false;
                    } else {
                        std::cout << "Grid lines enabled\n";
                        showGrid = true;
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
        if (showGrid) {
            window.draw(gridVertices);
        }
        window.display();
    }


	return 0;
}
