#include <windows.h>

#include "event/wnd.h"

#include "event/mouse.h"
#include "handler/mouse.h"
#include "constants/runtime.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (runtime_enabled) {
        switch (msg) {
            case WM_INPUT: {
                UINT size = sizeof(RAWINPUT);
                BYTE buffer[sizeof(RAWINPUT)];

                GetRawInputData(
                    (HRAWINPUT) lParam,
                    RID_INPUT,
                    buffer,
                    &size,
                    sizeof(RAWINPUTHEADER)
                );

                RAWINPUT *raw = (RAWINPUT *) buffer;

                if (raw->header.dwType == RIM_TYPEMOUSE) {
                    LONG dx = raw->data.mouse.lLastX;
                    LONG dy = raw->data.mouse.lLastY;

                    mouse_move(dx, dy);
                }

                return 0;
            }

            case WM_DESTROY: {
                PostQuitMessage(0);
                return 0;
            }
        }
    }

    return DefWindowProc(
        hwnd,
        msg,
        wParam,
        lParam
    );
}
