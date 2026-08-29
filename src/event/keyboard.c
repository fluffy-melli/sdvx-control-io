#include <windows.h>

#include "event/keyboard.h"

#include "key/input.h"
#include "key/constant.h"
#include "runtime/value.h"

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        KBDLLHOOKSTRUCT* keyboard = (KBDLLHOOKSTRUCT*) lParam;

        DWORD code = keyboard->scanCode;

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (code == KEY_ENABLED) {
                runtime_enabled = !runtime_enabled;

                if (runtime_enabled) {
                    POINT point;
                    GetCursorPos(&point);
                    runtime_init(point.x, point.y);
                }

                return 1;
            }

            if ((code >= KEY_NUMBER_1 && code <= KEY_NUMBER_9) || code == KEY_NUMBER_0) {
                key_input(key_number_2_numpad(code), true);
                return 1;
            }
        }

        if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            if ((code >= KEY_NUMBER_1 && code <= KEY_NUMBER_9) || code == KEY_NUMBER_0) {
                key_input(key_number_2_numpad(code), false);
                return 1;
            }
        }
    }

    return CallNextHookEx(
        NULL,
        nCode,
        wParam,
        lParam
    );
}
