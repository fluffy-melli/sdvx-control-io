#include "handler/mouse.h"

#include "constants/key.h"
#include "constants/runtime.h"
#include "constants/interval.h"
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

    LONGLONG knob_left_idle_elapsed = now.QuadPart - runtime_knob_left_last_active.QuadPart;
    LONGLONG knob_right_idle_elapsed = now.QuadPart - runtime_knob_right_last_active.QuadPart;
    LONGLONG knob_up_idle_elapsed = now.QuadPart - runtime_knob_up_last_active.QuadPart;
    LONGLONG knob_down_idle_elapsed = now.QuadPart - runtime_knob_down_last_active.QuadPart;

    LONGLONG key_repeat_interval = runtime_frequency.QuadPart * KEY_REPEAT_INTERVAL_MS / 1000;
    LONGLONG key_release_grace_period = runtime_frequency.QuadPart * KEY_RELEASE_GRACE_PERIOD_MS / 1000;

    if (knob_left) {
        QueryPerformanceCounter(&runtime_knob_left_last_active);
        if (knob_left_elapsed >= key_repeat_interval) {
            QueryPerformanceCounter(&runtime_knob_left_last_update);
            keyboard_input(KEY_1, true);
        }
    } else if (runtime_knob_left_last_active.QuadPart != 0) {
        if (knob_left_idle_elapsed >= key_release_grace_period) {
            runtime_knob_left_last_active.QuadPart = 0;
            keyboard_input(KEY_1, false);
        }
    }

    if (knob_right) {
        QueryPerformanceCounter(&runtime_knob_right_last_active);
        if (knob_right_elapsed >= key_repeat_interval) {
            QueryPerformanceCounter(&runtime_knob_right_last_update);
            keyboard_input(KEY_2, true);
        }
    } else if (runtime_knob_right_last_active.QuadPart != 0) {
        if (knob_right_idle_elapsed >= key_release_grace_period) {
            runtime_knob_right_last_active.QuadPart = 0;
            keyboard_input(KEY_2, false);
        }
    }

    if (knob_up) {
        QueryPerformanceCounter(&runtime_knob_up_last_active);
        if (knob_up_elapsed >= key_repeat_interval) {
            QueryPerformanceCounter(&runtime_knob_up_last_update);
            keyboard_input(KEY_3, true);
        }
    } else if (runtime_knob_up_last_active.QuadPart != 0) {
        if (knob_up_idle_elapsed >= key_release_grace_period) {
            runtime_knob_up_last_active.QuadPart = 0;
            keyboard_input(KEY_3, false);
        }
    }

    if (knob_down) {
        QueryPerformanceCounter(&runtime_knob_down_last_active);
        if (knob_down_elapsed >= key_repeat_interval) {
            QueryPerformanceCounter(&runtime_knob_down_last_update);
            keyboard_input(KEY_4, true);
        }
    } else if (runtime_knob_down_last_active.QuadPart != 0) {
        if (knob_down_idle_elapsed >= key_release_grace_period) {
            runtime_knob_down_last_active.QuadPart = 0;
            keyboard_input(KEY_4, false);
        }
    }
}
