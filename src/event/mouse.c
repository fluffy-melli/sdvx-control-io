#include <stdio.h>
#include <windows.h>

#include "event/mouse.h"

#include "constants/runtime.h"

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (runtime_enabled && nCode >= 0 && wParam == WM_MOUSEMOVE) {
        return 1;
    }

    return CallNextHookEx(
        NULL,
        nCode,
        wParam,
        lParam
    );
}
