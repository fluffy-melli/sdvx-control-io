#include <windows.h>

#include "event/wnd.h"
#include "event/mouse.h"
#include "event/keyboard.h"
#include "constants/runtime.h"

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "sdvx-control-io-window";
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        wc.lpszClassName,
        "sdvx-control-io",
        0,
        0, 0,
        0, 0,
        HWND_MESSAGE,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 1;
    }

    RAWINPUTDEVICE rid;
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02;
    rid.dwFlags = RIDEV_INPUTSINK;
    rid.hwndTarget = hwnd;

    runtime_init();
    if (!RegisterRawInputDevices(&rid, 1, sizeof(rid))) {
        return 1;
    }

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

    runtime_deinit();
    UnhookWindowsHookEx(mouseHook);
    UnhookWindowsHookEx(keyboardHook);

    return 0;
}
