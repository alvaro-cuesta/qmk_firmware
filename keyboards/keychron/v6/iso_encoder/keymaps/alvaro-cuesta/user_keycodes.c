#include QMK_KEYBOARD_H
#include "user_keycodes.h"
// Do I need these includes, or is the `QMK_KEYBOARD_H` above just not working for me?
#include "rgb_matrix.h"

#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)

enum rgb_push_state {
    RGB_PUSH_VAL = 0x1,
    RGB_PUSH_HUE = 0x2,
    RGB_PUSH_SAT = 0x4,
    RGB_PUSH_SPD = 0x8
};

enum rgb_push_state push_state = RGB_PUSH_VAL;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case RGBE_IN:
            #ifndef RGB_TRIGGER_ON_KEYDOWN
                if (!record->event.pressed) {
            #else
                if (record->event.pressed) {
            #endif
                switch (push_state) {
                    case RGB_PUSH_VAL:
                        rgb_matrix_increase_val();
                        break;
                    case RGB_PUSH_HUE:
                        rgb_matrix_increase_hue();
                        break;
                    case RGB_PUSH_SAT:
                        rgb_matrix_increase_sat();
                        break;
                    case RGB_PUSH_SPD:
                        rgb_matrix_increase_speed();
                        break;
                }
            }
            return false;
        case RGBE_DE:
            #ifndef RGB_TRIGGER_ON_KEYDOWN
                if (!record->event.pressed) {
            #else
                if (record->event.pressed) {
            #endif
                switch (push_state) {
                    case RGB_PUSH_VAL:
                        rgb_matrix_decrease_val();
                        break;
                    case RGB_PUSH_HUE:
                        rgb_matrix_decrease_hue();
                        break;
                    case RGB_PUSH_SAT:
                        rgb_matrix_decrease_sat();
                        break;
                    case RGB_PUSH_SPD:
                        rgb_matrix_decrease_speed();
                        break;
                }
            }
            return false;
        case RGBE_HU:
            if (record->event.pressed) {
                push_state = RGB_PUSH_HUE;
            } else {
                push_state = RGB_PUSH_VAL;
            }
            return false;
        case RGBE_SA:
            if (record->event.pressed) {
                push_state = RGB_PUSH_SAT;
            } else {
                push_state = RGB_PUSH_VAL;
            }
            return false;
        case RGBE_SP:
            if (record->event.pressed) {
                push_state = RGB_PUSH_SPD;
            } else {
                push_state = RGB_PUSH_VAL;
            }
            return false;
    }

    return true;
}

#endif // RGB_MATRIX_ENABLE...
