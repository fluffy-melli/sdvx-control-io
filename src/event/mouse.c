#include <stdio.h>
#include <windows.h>

#include "event/mouse.h"

#include "key/input.h"
#include "key/constant.h"
#include "runtime/value.h"

void wait_interval(LARGE_INTEGER started, LARGE_INTEGER interval) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    LONGLONG elapsed = now.QuadPart - started.QuadPart;
    LONGLONG remaining = interval.QuadPart - elapsed;

    if (remaining > 0) {
        DWORD milliseconds = (DWORD) (((double) remaining * 1000.0 / runtime_frequency.QuadPart) + 0.999);
        Sleep(milliseconds);
    }
}


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (runtime_enabled && nCode >= 0 && wParam == WM_MOUSEMOVE) {
        MSLLHOOKSTRUCT *mouse = (MSLLHOOKSTRUCT *) lParam;

        POINT point = mouse->pt;

        LONG dx = point.x - runtime_mouse_x;
        LONG dy = point.y - runtime_mouse_y;

        if (dx == 0) {
            if (runtime_knob_left) {
                wait_interval(runtime_knob_left_maintain, runtime_mouse_interval);
            }

            runtime_knob_left = false;
            runtime_knob_left_maintain.QuadPart = 0;

            if (runtime_knob_right) {
                wait_interval(runtime_knob_right_maintain, runtime_mouse_interval);
            }

            runtime_knob_right = false;
            runtime_knob_right_maintain.QuadPart = 0;
        }

        if (dy == 0) {
            if (runtime_knob_up) {
                wait_interval(runtime_knob_up_maintain, runtime_mouse_interval);
            }

            runtime_knob_up = false;
            runtime_knob_up_maintain.QuadPart = 0;

            if (runtime_knob_down) {
                wait_interval(runtime_knob_down_maintain, runtime_mouse_interval);
            }

            runtime_knob_down = false;
            runtime_knob_down_maintain.QuadPart = 0;
        }

        if (dx < 0) {
            if (!runtime_knob_left) {
                QueryPerformanceCounter(&runtime_knob_left_maintain);
            }

            runtime_knob_left = true;
        }

        if (dx > 0) {
            if (!runtime_knob_right) {
                QueryPerformanceCounter(&runtime_knob_right_maintain);
            }

            runtime_knob_right = true;
        }

        if (dy < 0) {
            if (!runtime_knob_up) {
                QueryPerformanceCounter(&runtime_knob_up_maintain);
            }

            runtime_knob_up = true;
        }

        if (dy > 0) {
            if (!runtime_knob_down) {
                QueryPerformanceCounter(&runtime_knob_down_maintain);
            }
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

        //LONGLONG left_elapsed_ms = 0;
        //LONGLONG right_elapsed_ms = 0;
        //LONGLONG up_elapsed_ms = 0;
        //LONGLONG down_elapsed_ms = 0;

        //LARGE_INTEGER now = { 0 };
        //QueryPerformanceCounter(&now);

        //if (runtime_knob_left_maintain.QuadPart > 0) {
        //    left_elapsed_ms = (LONGLONG) ((double) (now.QuadPart - runtime_knob_left_maintain.QuadPart) * 1000.0 / (double) runtime_frequency.QuadPart);
        //}

        //if (runtime_knob_right_maintain.QuadPart > 0) {
        //    right_elapsed_ms = (LONGLONG) ((double) (now.QuadPart - runtime_knob_right_maintain.QuadPart) * 1000.0 / (double) runtime_frequency.QuadPart);
        //}

        //if (runtime_knob_up_maintain.QuadPart > 0) {
        //    up_elapsed_ms = (LONGLONG) ((double) (now.QuadPart - runtime_knob_up_maintain.QuadPart) * 1000.0 / (double) runtime_frequency.QuadPart);
        //}

        //if (runtime_knob_down_maintain.QuadPart > 0) {
        //    down_elapsed_ms = (LONGLONG) ((double) (now.QuadPart - runtime_knob_down_maintain.QuadPart) * 1000.0 / (double) runtime_frequency.QuadPart);
        //}

        //if (left_elapsed_ms != 0 || right_elapsed_ms != 0 || up_elapsed_ms != 0 || down_elapsed_ms != 0) {
        //    printf("%lld ms | %lld ms | %lld ms | %lld ms\n", left_elapsed_ms, right_elapsed_ms, up_elapsed_ms, down_elapsed_ms);
        //}

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
