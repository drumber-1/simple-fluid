#pragma once

class InputState {
public:
    bool toggle_velocity = false;
    bool toggle_grid = false;
    bool toggle_paused = false;
    bool do_step = false;

    bool add_density = false;
    bool add_velocity_start = false;
    bool add_velocity = false;

    float mouse_x = false;
    float mouse_y = false;

    void reset() {
        toggle_velocity = false;
        toggle_grid = false;
        toggle_paused = false;
        do_step = false;

        add_velocity_start = false;
    }
};