#include <windows.h>

#include "runtime/value.h"

void runtime_init(LONG mouse_x, LONG mouse_y) {
    runtime_mouse_x = mouse_x;
    runtime_mouse_y = mouse_y;

    runtime_enabled = true;

    runtime_knob_up = false;
    runtime_knob_left = false;
    runtime_knob_down = false;
    runtime_knob_right = false;

    QueryPerformanceFrequency(&runtime_frequency);

    runtime_knob_up_maintain.QuadPart = 0;
    runtime_knob_left_maintain.QuadPart = 0;
    runtime_knob_down_maintain.QuadPart = 0;
    runtime_knob_right_maintain.QuadPart = 0;
}
