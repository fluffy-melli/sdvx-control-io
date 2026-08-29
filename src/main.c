#include <windows.h>

#include "event/mouse.h"
#include "event/keyboard.h"

int main() {
    HHOOK mouseHook = SetWindowsHookEx(
        WH_MOUSE_LL,
        MouseProc,
        NULL,
        0
    );

    if (mouseHook == NULL) {
        return 1;
    }

    HHOOK keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        KeyboardProc,
        NULL,
        0
    );

    if (keyboardHook == NULL) {
        UnhookWindowsHookEx(mouseHook);
        return 1;
    }

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    UnhookWindowsHookEx(mouseHook);

    return 0;
}
