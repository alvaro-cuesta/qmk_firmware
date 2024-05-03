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

#include "host.h"
#include "keycode_config.h"
#include "rgb_matrix.h"

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX) || defined(NKRO_LED_INDEX))

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    #if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        if (!rgb_matrix_get_flags()) {
        #endif // !FORCE_TURN_OFF_INDICATORS
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        }
        #endif // !FORCE_TURN_OFF_INDICATORS
    }
    #endif // CAPS_LOCK_LED_INDEX

    #if defined(NUM_LOCK_LED_INDEX)
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        if (!rgb_matrix_get_flags()) {
        #endif // !FORCE_TURN_OFF_INDICATORS
            RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 0, 0, 0);
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        }
        #endif // !FORCE_TURN_OFF_INDICATORS
    }
    #endif // NUM_LOCK_LED_INDEX

    #if defined(SCROLL_LOCK_LED_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(SCROLL_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        if (!rgb_matrix_get_flags()) {
        #endif // !FORCE_TURN_OFF_INDICATORS
            RGB_MATRIX_INDICATOR_SET_COLOR(SCROLL_LOCK_LED_INDEX, 0, 0, 0);
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        }
        #endif // !FORCE_TURN_OFF_INDICATORS
    }
    #endif // SCROLL_LOCK_LED_INDEX

    #if defined(NKRO_LED_INDEX)
    if (keymap_config.nkro) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NKRO_LED_INDEX, 255, 255, 255);
    } else {
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        if (!rgb_matrix_get_flags()) {
        #endif // !FORCE_TURN_OFF_INDICATORS
            RGB_MATRIX_INDICATOR_SET_COLOR(NKRO_LED_INDEX, 0, 0, 0);
        #if !defined(FORCE_TURN_OFF_INDICATORS)
        }
        #endif // !FORCE_TURN_OFF_INDICATORS
    }
    #endif // NKRO_LED_INDEX

    // We've overriden the default behavior so no need to go back to KB
    return false;
}

#endif // RGB_MATRIX_ENABLE...
