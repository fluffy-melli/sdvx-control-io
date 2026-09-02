#pragma once

#include <windows.h>

void mouse_move_event(LONG dx, LONG dy);

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
