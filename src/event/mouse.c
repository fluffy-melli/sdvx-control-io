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

        if (dx < 0) {
            if (!runtime_knob_left) {
                key_input(KEY_1, true);
                runtime_knob_left = true;
            }
        } else {
            if (runtime_knob_left) {
                key_input(KEY_1, false);
                runtime_knob_left = false;
            }
        }

        if (dx > 0) {
            if (!runtime_knob_right) {
                key_input(KEY_2, true);
                runtime_knob_right = true;
            }
        } else {
            if (runtime_knob_right) {
                key_input(KEY_2, false);
                runtime_knob_right = false;
            }
        }

        if (dy < 0) {
            if (!runtime_knob_up) {
                key_input(KEY_3, true);
                runtime_knob_up = true;
            }
        } else {
            if (runtime_knob_up) {
                key_input(KEY_3, false);
                runtime_knob_up = false;
            }
        }

        if (dy > 0) {
            if (!runtime_knob_down) {
                key_input(KEY_4, true);
                runtime_knob_down = true;
            }
        } else {
            if (runtime_knob_down) {
                key_input(KEY_4, false);
                runtime_knob_down = false;
            }
        }

        return 1;
    }

    return CallNextHookEx(
        NULL,
        nCode,
        wParam,
        lParam
    );
}
