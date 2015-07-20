#pragma once

#include <SFML/Graphics.hpp>
#include "../fluid/Grid.hpp"

template <size_t NX, size_t NY>
class GridRenderer {
public:
    GridRenderer(std::string colour_map,
                 float pixels_per_unit,
                 float density_scale,
                 float velocity_scale,
                 const Grid<NX, NY> &grid);

    void initialiseVertices(const Grid<NX, NY> &grid);
    void initialiseDensityVertices(const Grid<NX, NY> &grid);
    void initialiseVelocityVertices(const Grid<NX, NY> &grid);
    void initialiseGridVertices(const Grid<NX, NY> &grid);

    void updateVertices(const Grid<NX, NY> &grid);
    void updateDensityVertices(const Grid<NX, NY> &grid);
    void updateVelocityVertices(const Grid<NX, NY> &grid);

    void render(sf::RenderWindow& window);

    bool draw_velocity;
    bool draw_grid;
private:
    sf::VertexArray vertices_density;
    sf::VertexArray vertices_velocity;
    sf::VertexArray vertices_grid;

    sf::Texture colour_map;

    const float pixels_per_cell_x;
    const float pixels_per_cell_y;
    float scale_density;
    float scale_velocity;

    const sf::Color color_velocity = sf::Color::Red;
    const sf::Color color_grid = sf::Color::Blue;
};

template <size_t NX,size_t NY>
GridRenderer<NX, NY>::GridRenderer(std::string cmap,
                                   float pixels_per_unit,
                                   float density_scale,
                                   float velocity_scale,
                                   const Grid<NX, NY> &grid) :
        draw_velocity(false),
        draw_grid(false),
        pixels_per_cell_x(pixels_per_unit * grid.units_per_cell_x),
        pixels_per_cell_y(pixels_per_unit * grid.units_per_cell_y),
        scale_density(density_scale),
        scale_velocity(velocity_scale) {
    colour_map.loadFromFile(cmap);

    vertices_density.setPrimitiveType(sf::Quads);
    vertices_density.resize((unsigned int)(NX * NY * 4));

    vertices_velocity.setPrimitiveType(sf::Lines);
    vertices_velocity.resize((unsigned int)(NX * NY * 2));

    vertices_grid.setPrimitiveType(sf::Lines);
    vertices_grid.resize((unsigned int)(2 * (NX + NY + 2)));
};

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::initialiseVertices(const Grid<NX, NY> &grid) {
    initialiseDensityVertices(grid);
    initialiseGridVertices(grid);
    initialiseVelocityVertices(grid);
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::initialiseDensityVertices(const Grid<NX, NY> &grid) {
    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            sf::Vertex* quad = &vertices_density[(i + j * NX) * 4];

            quad[0].position = sf::Vector2f(pixels_per_cell_x *  i     , pixels_per_cell_y * (j    ));
            quad[1].position = sf::Vector2f(pixels_per_cell_x * (i + 1), pixels_per_cell_y * (j    ));
            quad[2].position = sf::Vector2f(pixels_per_cell_x * (i + 1), pixels_per_cell_y * (j + 1));
            quad[3].position = sf::Vector2f(pixels_per_cell_x * (i    ), pixels_per_cell_y * (j + 1));
        }
    }
    updateDensityVertices(grid);
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::initialiseVelocityVertices(const Grid<NX, NY> &grid) {
    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            sf::Vertex* line = &vertices_velocity[(i + j * NX) * 2];

            float xstart = pixels_per_cell_x * (i + 0.5f);
            float ystart = pixels_per_cell_y * (j + 0.5f);

            line[0].position = sf::Vector2f(xstart, ystart);

            line[0].color = color_velocity;
            line[1].color = color_velocity;
        }
    }
    updateVelocityVertices(grid);
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::initialiseGridVertices(const Grid<NX, NY> &grid) {
    for (size_t i = 0; i <= NX; ++i) {
        sf::Vertex* line = &vertices_grid[2 * i];

        line[0].position = sf::Vector2f(i * pixels_per_cell_x, 0);
        line[1].position = sf::Vector2f(i * pixels_per_cell_x, NY * pixels_per_cell_y);

        line[0].color = color_grid;
        line[1].color = color_grid;
    }
    for (size_t j = 0; j <= NY; ++j) {
        sf::Vertex* line = &vertices_grid[2 * (NX + 1 + j)];

        line[0].position = sf::Vector2f(0, j * pixels_per_cell_y);
        line[1].position = sf::Vector2f(NX * pixels_per_cell_x, j * pixels_per_cell_y);

        line[0].color = color_grid;
        line[1].color = color_grid;
    }
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::updateVertices(const Grid<NX, NY> &grid) {
    updateDensityVertices(grid);
    updateVelocityVertices(grid);
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::updateDensityVertices(const Grid<NX, NY> &grid) {
    int cmap_size = colour_map.getSize().x;

    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            sf::Vertex* quad = &vertices_density[(i + j * NX) * 4];

            int col_x = (int)(cmap_size * grid.density(i, j) / scale_density);

            for (int q = 0; q < 4; ++q) {
                quad[q].texCoords = sf::Vector2f(col_x, 0);
            }
        }
    }
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::updateVelocityVertices(const Grid<NX, NY> &grid) {
    for (size_t i = 0; i < NX; ++i) {
        for (size_t j = 0; j < NY; ++j) {
            sf::Vertex* line = &vertices_velocity[(i + j * NX) * 2];

            float xstart = pixels_per_cell_x * (i + 0.5f);
            float ystart = pixels_per_cell_y * (j + 0.5f);

            float xoffset = pixels_per_cell_x *  grid.velocity_x(i, j) * scale_velocity;
            float yoffset = pixels_per_cell_y *  grid.velocity_y(i, j) * scale_velocity;

            line[0].position = sf::Vector2f(xstart, ystart);
            line[1].position = sf::Vector2f(xstart + xoffset, ystart + yoffset);;
        }
    }
}

template <size_t NX, size_t NY>
void GridRenderer<NX, NY>::render(sf::RenderWindow &window) {
    window.draw(vertices_density, &colour_map);
    if (draw_velocity) {
        window.draw(vertices_velocity);
    }
    if (draw_grid) {
        window.draw(vertices_grid);
    }
}
