#pragma once

class InputState {
public:
    bool toggle_velocity = false;
    bool toggle_grid = false;
    bool toggle_paused = false;
    bool do_step = false;

    bool mouse_left_down = false;
    bool mouse_left_down_last = false;
    bool mouse_right_down = false;
    bool mouse_right_down_last = false;

    float mouse_x = false;
    float mouse_y = false;

    void reset() {
        toggle_velocity = false;
        toggle_grid = false;
        toggle_paused = false;
        do_step = false;

        mouse_left_down_last = false;
        mouse_right_down_last = false;
    }
};