#pragma once

#include <SFML/Graphics.hpp>
#include "InputState.hpp"

class InputHandler {
public:
    void process_input(sf::RenderWindow& window);
    InputState state;
};

void InputHandler::process_input(sf::RenderWindow &window) {
    sf::Event event;
    state.reset();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::S) {
                state.do_step = true;
            } else if (event.key.code == sf::Keyboard::Space) {
                state.toggle_paused = true;
            } else if (event.key.code == sf::Keyboard::V) {
                state.toggle_velocity = true;
            } else if (event.key.code == sf::Keyboard::G) {
               state.toggle_grid = true;
            }
        } else if (event.type == sf::Event::MouseButtonPressed) {
            state.mouse_x = event.mouseButton.x;
            state.mouse_y = event.mouseButton.y;
            if (event.mouseButton.button == sf::Mouse::Left) {
                state.mouse_left_down = true;
                state.mouse_left_down_last = true;
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                state.mouse_right_down = true;
                state.mouse_right_down_last = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                state.mouse_left_down = false;
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                state.mouse_right_down = false;
            }
        } else if (event.type == sf::Event::MouseMoved) {
            state.mouse_x = event.mouseMove.x;
            state.mouse_y = event.mouseMove.y;
        }
    }
}
