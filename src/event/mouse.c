#include <stdio.h>
#include <windows.h>

#include "event/mouse.h"

#include "key/input.h"
#include "key/constant.h"
#include "runtime/value.h"

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (runtime_enabled && nCode >= 0 && wParam == WM_MOUSEMOVE) {
        MSLLHOOKSTRUCT *mouse = (MSLLHOOKSTRUCT *) lParam;

        POINT point = mouse->pt;

        LONG dx = point.x - runtime_mouse_x;
        LONG dy = point.y - runtime_mouse_y;

        if (dx == 0) {
            runtime_knob_left = false;
            runtime_knob_right = false;
        }

        if (dy == 0) {
            runtime_knob_up = false;
            runtime_knob_down = false;
        }

        if (dx < 0) {
            runtime_knob_left = true;
        }

        if (dx > 0) {
            runtime_knob_right = true;
        }

        if (dy < 0) {
            runtime_knob_up = true;
        }

        if (dy > 0) {
            runtime_knob_down = true;
        }

        if (runtime_knob_left) {
            key_input(KEY_1, true);
        } else {
            key_input(KEY_1, false);
        }

        if (runtime_knob_right) {
            key_input(KEY_2, true);
        } else {
            key_input(KEY_2, false);
        }

        if (runtime_knob_up) {
            key_input(KEY_3, true);
        } else {
            key_input(KEY_3, false);
        }

        if (runtime_knob_down) {
            key_input(KEY_4, true);
        } else {
            key_input(KEY_4, false);
        }

        SetCursorPos(runtime_mouse_x, runtime_mouse_y);

        return 1;
    }

    return CallNextHookEx(
        NULL,
        nCode,
        wParam,
        lParam
    );
}
