#include <windows.h>

#include "constants/runtime.h"

#include "constants/key.h"
#include "handler/keyboard.h"

void runtime_init() {
    runtime_deinit();

    runtime_enabled = false;

    QueryPerformanceFrequency(&runtime_frequency);

    runtime_knob_up_last_update.QuadPart = 0;
    runtime_knob_left_last_update.QuadPart = 0;
    runtime_knob_down_last_update.QuadPart = 0;
    runtime_knob_right_last_update.QuadPart = 0;
}

void runtime_deinit() {
    if (runtime_knob_left_last_update.QuadPart != 0) {
        runtime_knob_left_last_update.QuadPart = 0;
        keyboard_input(KEY_1, false);
    }

    if (runtime_knob_right_last_update.QuadPart != 0) {
        runtime_knob_right_last_update.QuadPart = 0;
        keyboard_input(KEY_2, false);
    }

    if (runtime_knob_up_last_update.QuadPart != 0) {
        runtime_knob_up_last_update.QuadPart = 0;
        keyboard_input(KEY_3, false);
    }

    if (runtime_knob_down_last_update.QuadPart != 0) {
        runtime_knob_down_last_update.QuadPart = 0;
        keyboard_input(KEY_4, false);
    }
}
