#include <stdio.h>
#include <windows.h>

#include "event/mouse.h"

#include "key/input.h"
#include "key/constant.h"
#include "runtime/value.h"

void mouse_move_event(LONG dx, LONG dy) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    bool knob_left = dx < 0;
    bool knob_right = dx > 0;

    bool knob_up = dy < 0;
    bool knob_down = dy > 0;

    if (knob_left) {
        LONGLONG elapsed = now.QuadPart - runtime_knob_left_last_update.QuadPart;
        if (elapsed >= runtime_frequency.QuadPart * 16 / 1000) {
            QueryPerformanceCounter(&runtime_knob_left_last_update);
            key_input(KEY_1, true);
        }
    } else if (runtime_knob_left_last_update.QuadPart != 0) {
        runtime_knob_left_last_update.QuadPart = 0;
        key_input(KEY_1, false);
    }

    if (knob_right) {
        LONGLONG elapsed = now.QuadPart - runtime_knob_right_last_update.QuadPart;
        if (elapsed >= runtime_frequency.QuadPart * 16 / 1000) {
            QueryPerformanceCounter(&runtime_knob_right_last_update);
            key_input(KEY_2, true);
        }
    } else if (runtime_knob_right_last_update.QuadPart != 0) {
        runtime_knob_right_last_update.QuadPart = 0;
        key_input(KEY_2, false);
    }

    if (knob_up) {
        LONGLONG elapsed = now.QuadPart - runtime_knob_up_last_update.QuadPart;
        if (elapsed >= runtime_frequency.QuadPart * 16 / 1000) {
            QueryPerformanceCounter(&runtime_knob_up_last_update);
            key_input(KEY_3, true);
        }
    } else if (runtime_knob_up_last_update.QuadPart != 0) {
        runtime_knob_up_last_update.QuadPart = 0;
        key_input(KEY_3, false);
    }

    if (knob_down) {
        LONGLONG elapsed = now.QuadPart - runtime_knob_down_last_update.QuadPart;
        if (elapsed >= runtime_frequency.QuadPart * 16 / 1000) {
            QueryPerformanceCounter(&runtime_knob_down_last_update);
            key_input(KEY_4, true);
        }
    } else if (runtime_knob_down_last_update.QuadPart != 0) {
        runtime_knob_down_last_update.QuadPart = 0;
        key_input(KEY_4, false);
    }
}
