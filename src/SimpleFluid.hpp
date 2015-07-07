#pragma once

#include "parameters.hpp"
#include "fluid/Grid.hpp"
#include "graphics/GridRenderer.hpp"
#include "input/InputState.hpp"
#include "input/FluidInteractor.hpp"

namespace simplefluid {
    class SimpleFluid {
    public:
        SimpleFluid();

        void update(float dt, const InputState& inputState);

        void render(sf::RenderWindow &window);

    private:
        Grid<NCELLS_X, NCELLS_Y> grid;
        GridRenderer<NCELLS_X, NCELLS_Y> grid_renderer;
        FluidInteractor<NCELLS_X, NCELLS_Y> fluidinteractor;

        bool fluid_paused = false;
    };

    SimpleFluid::SimpleFluid() : grid(CELL_SPACING),
                                 grid_renderer(COLOUR_MAP, PIXELS_PER_CELL, SCALE_RHO, SCALE_VELOCITY) {
        grid_renderer.initialiseVertices(grid);
    }

    void SimpleFluid::update(float dt, const InputState& inputState) {

        if (inputState.toggle_paused) {
            fluid_paused = !fluid_paused;
        }

        if (inputState.toggle_velocity) {
            grid_renderer.draw_velocity = !grid_renderer.draw_velocity;
        }

        if (inputState.toggle_grid) {
            grid_renderer.draw_grid = !grid_renderer.draw_grid;
        }

        if (inputState.do_step && fluid_paused) {
            grid.step(0.4f);
        }

        fluidinteractor.update(dt, inputState, grid);

        if (!fluid_paused) {
            grid.step(dt);
            grid_renderer.updateVertices(grid);
        }
    }

    void SimpleFluid::render(sf::RenderWindow &window) {
        grid_renderer.render(window);
    }
}
