#include "key/constant.h"

int key_number_2_numpad(int number) {
    switch (number) {
        case KEY_NUMBER_0: {
            return KEY_NUMPAD_0;
        }

        case KEY_NUMBER_1: {
            return KEY_NUMPAD_1;
        }

        case KEY_NUMBER_2: {
            return KEY_NUMPAD_2;
        }

        case KEY_NUMBER_3: {
            return KEY_NUMPAD_3;
        }

        case KEY_NUMBER_4: {
            return KEY_NUMPAD_4;
        }

        case KEY_NUMBER_5: {
            return KEY_NUMPAD_5;
        }

        case KEY_NUMBER_6: {
            return KEY_NUMPAD_6;
        }

        case KEY_NUMBER_7: {
            return KEY_NUMPAD_7;
        }

        case KEY_NUMBER_8: {
            return KEY_NUMPAD_8;
        }

        case KEY_NUMBER_9: {
            return KEY_NUMPAD_9;
        }
    }

    return 0;
}
