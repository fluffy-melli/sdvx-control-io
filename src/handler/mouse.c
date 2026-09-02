#include "handler/mouse.h"

#include "constants/key.h"
#include "constants/runtime.h"
#include "handler/keyboard.h"

void mouse_move(LONG dx, LONG dy) {
    bool knob_left = dx < 0;
    bool knob_right = dx > 0;

    bool knob_up = dy < 0;
    bool knob_down = dy > 0;

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    LONGLONG knob_left_elapsed = now.QuadPart - runtime_knob_left_last_update.QuadPart;
    LONGLONG knob_right_elapsed = now.QuadPart - runtime_knob_right_last_update.QuadPart;

    LONGLONG knob_up_elapsed = now.QuadPart - runtime_knob_up_last_update.QuadPart;
    LONGLONG knob_down_elapsed = now.QuadPart - runtime_knob_down_last_update.QuadPart;

    LONGLONG interval = runtime_frequency.QuadPart * 8 / 1000;

    if (knob_left) {
        if (knob_left_elapsed >= interval) {
            QueryPerformanceCounter(&runtime_knob_left_last_update);
            keyboard_input(KEY_1, true);
        }
    } else if (runtime_knob_left_last_update.QuadPart != 0) {
        runtime_knob_left_last_update.QuadPart = 0;
        keyboard_input(KEY_1, false);
    }

    if (knob_right) {
        if (knob_right_elapsed >= interval) {
            QueryPerformanceCounter(&runtime_knob_right_last_update);
            keyboard_input(KEY_2, true);
        }
    } else if (runtime_knob_right_last_update.QuadPart != 0) {
        runtime_knob_right_last_update.QuadPart = 0;
        keyboard_input(KEY_2, false);
    }

    if (knob_up) {
        if (knob_up_elapsed >= interval) {
            QueryPerformanceCounter(&runtime_knob_up_last_update);
            keyboard_input(KEY_3, true);
        }
    } else if (runtime_knob_up_last_update.QuadPart != 0) {
        runtime_knob_up_last_update.QuadPart = 0;
        keyboard_input(KEY_3, false);
    }

    if (knob_down) {
        if (knob_down_elapsed >= interval) {
            QueryPerformanceCounter(&runtime_knob_down_last_update);
            keyboard_input(KEY_4, true);
        }
    } else if (runtime_knob_down_last_update.QuadPart != 0) {
        runtime_knob_down_last_update.QuadPart = 0;
        keyboard_input(KEY_4, false);
    }
}
