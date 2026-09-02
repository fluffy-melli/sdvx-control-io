#pragma once

#include <stdbool.h>
#include <windows.h>

bool runtime_enabled;

LARGE_INTEGER runtime_frequency;

LARGE_INTEGER runtime_knob_up_last_update;
LARGE_INTEGER runtime_knob_left_last_update;
LARGE_INTEGER runtime_knob_down_last_update;
LARGE_INTEGER runtime_knob_right_last_update;

LARGE_INTEGER runtime_knob_up_last_active;
LARGE_INTEGER runtime_knob_left_last_active;
LARGE_INTEGER runtime_knob_down_last_active;
LARGE_INTEGER runtime_knob_right_last_active;

void runtime_init();
void runtime_deinit();
