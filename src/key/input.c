#include <stdbool.h>
#include <windows.h>

#include "key/input.h"

void key_input(WORD scanCode, bool down) {
    INPUT input = {0};

    input.type = INPUT_KEYBOARD;
    input.ki.wScan = scanCode;
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    if (!down) {
        input.ki.dwFlags |= KEYEVENTF_KEYUP;
    }

    SendInput(1, &input, sizeof(INPUT));
}
