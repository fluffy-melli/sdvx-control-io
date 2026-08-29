#pragma once

#include <windows.h>

void wait_interval(LARGE_INTEGER started, LARGE_INTEGER interval);

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
