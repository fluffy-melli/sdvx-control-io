#pragma once

#include <stdbool.h>

LONG runtime_mouse_x;
LONG runtime_mouse_y;

bool runtime_enabled;

bool runtime_knob_up;
bool runtime_knob_left;
bool runtime_knob_down;
bool runtime_knob_right;

void runtime_init(LONG mouse_x, LONG mouse_y);
void runtime_deinit();
