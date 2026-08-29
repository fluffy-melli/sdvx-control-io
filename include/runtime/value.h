#pragma once

#include <stdbool.h>

LONG runtime_mouse_x;
LONG runtime_mouse_y;

bool runtime_enabled;

bool runtime_knob_up;
bool runtime_knob_left;
bool runtime_knob_down;
bool runtime_knob_right;

LARGE_INTEGER runtime_frequency;

LARGE_INTEGER runtime_knob_up_maintain;
LARGE_INTEGER runtime_knob_left_maintain;
LARGE_INTEGER runtime_knob_down_maintain;
LARGE_INTEGER runtime_knob_right_maintain;

void runtime_init(LONG mouse_x, LONG mouse_y);
