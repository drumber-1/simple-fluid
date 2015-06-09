#include <iostream>

#include "fluid/Grid.hpp"
#include <SFML/Graphics.hpp>

const size_t GRIDX = 100;
const size_t GRIDY = 100;

const double RHOMAX = 10.0;

template <size_t NX, size_t NY>
void updateVertices(const Grid<NX, NY>& grid, sf::VertexArray& vertices) {

    float scaling = 5.0f;

    for (size_t i = 0; i < GRIDX; ++i) {
        for (size_t j = 0; j < GRIDY; ++j) {
            sf::Vertex* quad = &vertices[(i + j * GRIDX) * 4];

            int colx = (int)(256 * grid(FluidVariable::DENSITY, i, j) / RHOMAX);
            int coly = 0;

            quad[0].position = sf::Vector2f(scaling * i      , scaling * (j    ));
            quad[1].position = sf::Vector2f(scaling * (i + 1), scaling * (j    ));
            quad[2].position = sf::Vector2f(scaling * (i + 1), scaling * (j + 1));
            quad[3].position = sf::Vector2f(scaling * (i    ), scaling * (j + 1));

            for (int q = 0; q < 4; ++q) {
                quad[q].texCoords = sf::Vector2f(colx, coly);
            }
        }
    }
}

int main() {

    const float spacing = 1.0;

	Grid<GRIDX, GRIDY> grid(spacing);

    sf::Texture colourMap;
    colourMap.loadFromFile("res/colourmap.png");
    std::cout << "Colour map loaded, (" << colourMap.getSize().x << ", " << colourMap.getSize().y << ")\n";

    sf::VertexArray vertices;
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(GRIDX * GRIDY * 4);
    updateVertices(grid, vertices);

    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML TEST");

    sf::Clock clock;
    bool fluidPaused = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::S) {
                    std::cout << "Updating grid" << "\n";
                    grid.step(0.4);
                    updateVertices(grid, vertices);
                } else if (event.key.code == sf::Keyboard::Space) {
                    if (fluidPaused) {
                        std::cout << "Fluid unpaused\n";
                        fluidPaused = false;
                        clock.restart();
                    } else {
                        std::cout << "Fluid paused\n";
                        fluidPaused = true;
                    }
                }
            }
        }

        sf::Time elapsed = clock.restart();

        if (!fluidPaused) {
            grid.step(elapsed.asSeconds());
            updateVertices(grid, vertices);
        }

        window.clear();
        window.draw(vertices, &colourMap);
        window.display();
    }


	return 0;
}
