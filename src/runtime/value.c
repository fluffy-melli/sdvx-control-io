#include <windows.h>

#include "key/input.h"
#include "key/constant.h"
#include "runtime/value.h"

void runtime_init(LONG mouse_x, LONG mouse_y) {
    runtime_deinit();

    runtime_mouse_x = mouse_x;
    runtime_mouse_y = mouse_y;

    runtime_enabled = true;

    runtime_knob_left = false;
    runtime_knob_right = false;
    runtime_knob_up = false;
    runtime_knob_down = false;
}

void runtime_deinit() {
    if (runtime_knob_left) {
        key_input(KEY_1, false);
        runtime_knob_left = false;
    }

    if (runtime_knob_right) {
        key_input(KEY_2, false);
        runtime_knob_right = false;
    }

    if (runtime_knob_up) {
        key_input(KEY_3, false);
        runtime_knob_up = false;
    }

    if (runtime_knob_down) {
        key_input(KEY_4, false);
        runtime_knob_down = false;
    }
}
