/* Copyright 2024 @ Alvaro Cuesta (https://github.com/alvaro-cuesta/)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rgb_matrix.h"

#include "keychron_common.h"

#include "user_keycodes.h"

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
