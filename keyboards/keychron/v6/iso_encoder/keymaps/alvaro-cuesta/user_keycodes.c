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
    RGB_PUSH_NONE = 0x0,
    RGB_PUSH_HUE = 0x1,
    RGB_PUSH_SAT = 0x2,
    RGB_PUSH_SPD = 0x4,
    RGB_PUSH_EFF = 0x8
};

enum rgb_push_state push_state = RGB_PUSH_NONE;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) {
        return false;
    }

    switch (keycode) {
        /* RGB effect control */
        case RGBE_IN:
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif
                if (HAS_FLAGS(push_state, RGB_PUSH_HUE)) {
                    rgb_matrix_increase_hue();
                }

                if (HAS_FLAGS(push_state, RGB_PUSH_SAT)) {
                    rgb_matrix_increase_sat();
                }

                if (HAS_FLAGS(push_state, RGB_PUSH_SPD)) {
                    rgb_matrix_increase_speed();
                }

                if (HAS_FLAGS(push_state, RGB_PUSH_EFF)) {
                    rgb_matrix_step();
                }

                if (push_state == RGB_PUSH_NONE) {
                    rgb_matrix_increase_val();
                }
            }
            return false;
        case RGBE_DE:
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif
                if (HAS_FLAGS(push_state, RGB_PUSH_HUE)) {
                    rgb_matrix_decrease_hue();
                }

                if (HAS_FLAGS(push_state, RGB_PUSH_SAT)) {
                    rgb_matrix_decrease_sat();
                }

                if (HAS_FLAGS(push_state, RGB_PUSH_SPD)) {
                    rgb_matrix_decrease_speed();
                }

                if (HAS_FLAGS(push_state, RGB_PUSH_EFF)) {
                    rgb_matrix_step_reverse();
                }

                if (push_state == RGB_PUSH_NONE) {
                    rgb_matrix_decrease_val();
                }
            }
            return false;

        /* RGB effect modifiers */
        case RGBE_HU:
            if (record->event.pressed) {
                push_state |= RGB_PUSH_HUE;
            } else {
                push_state &= ~RGB_PUSH_HUE;
            }
            return false;
        case RGBE_SA:
            if (record->event.pressed) {
                push_state |= RGB_PUSH_SAT;
            } else {
                push_state &= ~RGB_PUSH_SAT;
            }
            return false;
        case RGBE_SP:
            if (record->event.pressed) {
                push_state |= RGB_PUSH_SPD;
            } else {
                push_state &= ~RGB_PUSH_SPD;
            }
            return false;
        case RGBE_EF:
            if (record->event.pressed) {
                push_state |= RGB_PUSH_EFF;
            } else {
                push_state &= ~RGB_PUSH_EFF;
            }
            return false;

        /* RGB modes */
        // TODO: Maybe we want to do this with RGB_MATRIX_EFFECT macro trick instead of having so much repetition
        //       But that means keycodes will change depending on, while on this solution keycodes are stable (but do nothing instead)
        //       Also possibly just subtract the value of the first mode keycode to get the mode index in the enum, and have a single block with many cases?
        // TODO: Can this instead be abstracted into macros?
        case RGBM_SOLID_COLOR:
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            }
            return false;
        case RGBM_ALPHAS_MODS:
            #ifdef ENABLE_RGB_MATRIX_ALPHAS_MODS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
            }
            #endif // ENABLE_RGB_MATRIX_ALPHAS_MODS
            return false;
        case RGBM_GRADIENT_UP_DOWN:
            #ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
            }
            #endif // ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
            return false;
        case RGBM_GRADIENT_LEFT_RIGHT:
            #ifdef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_GRADIENT_LEFT_RIGHT);
            }
            #endif // ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
            return false;
        case RGBM_BREATHING:
            #ifdef ENABLE_RGB_MATRIX_BREATHING
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BREATHING);
            }
            #endif // ENABLE_RGB_MATRIX_BREATHING
            return false;
        case RGBM_BAND_SAT:
            #ifdef ENABLE_RGB_MATRIX_BAND_SAT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BAND_SAT);
            }
            #endif // ENABLE_RGB_MATRIX_BAND_SAT
            return false;
        case RGBM_BAND_VAL:
            #ifdef ENABLE_RGB_MATRIX_BAND_VAL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BAND_VAL);
            }
            #endif // ENABLE_RGB_MATRIX_BAND_VAL
            return false;
        case RGBM_BAND_PINWHEEL_SAT:
            #ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BAND_PINWHEEL_SAT);
            }
            #endif // ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
            return false;
        case RGBM_BAND_PINWHEEL_VAL:
            #ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BAND_PINWHEEL_VAL);
            }
            #endif // ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
            return false;
        case RGBM_BAND_SPIRAL_SAT:
            #ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BAND_SPIRAL_SAT);
            }
            #endif // ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
            return false;
        case RGBM_BAND_SPIRAL_VAL:
            #ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_BAND_SPIRAL_VAL);
            }
            #endif // ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
            return false;
        case RGBM_CYCLE_ALL:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_ALL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_ALL
            return false;
        case RGBM_CYCLE_LEFT_RIGHT:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
            return false;
        case RGBM_CYCLE_UP_DOWN:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_UP_DOWN);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
            return false;
        case RGBM_RAINBOW_MOVING_CHEVRON:
            #ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON);
            }
            #endif // ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
            return false;
        case RGBM_CYCLE_OUT_IN:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_OUT_IN);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_OUT_IN
            return false;
        case RGBM_CYCLE_OUT_IN_DUAL:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_OUT_IN_DUAL);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
            return false;
        case RGBM_CYCLE_PINWHEEL:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_PINWHEEL);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
            return false;
        case RGBM_CYCLE_SPIRAL:
            #ifdef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
            }
            #endif // ENABLE_RGB_MATRIX_CYCLE_SPIRAL
            return false;
        case RGBM_DUAL_BEACON:
            #ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_DUAL_BEACON);
            }
            #endif // ENABLE_RGB_MATRIX_DUAL_BEACON
            return false;
        case RGBM_RAINBOW_BEACON:
            #ifdef ENABLE_RGB_MATRIX_RAINBOW_BEACON
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_RAINBOW_BEACON);
            }
            #endif // ENABLE_RGB_MATRIX_RAINBOW_BEACON
            return false;
        case RGBM_RAINBOW_PINWHEELS:
            #ifdef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_RAINBOW_PINWHEELS);
            }
            #endif // ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
            return false;
        case RGBM_FLOWER_BLOOMING:
            #ifdef ENABLE_RGB_MATRIX_FLOWER_BLOOMING
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_FLOWER_BLOOMING);
            }
            #endif // ENABLE_RGB_MATRIX_FLOWER_BLOOMING
            return false;
        case RGBM_RAINDROPS:
            #ifdef ENABLE_RGB_MATRIX_RAINDROPS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_RAINDROPS);
            }
            #endif // ENABLE_RGB_MATRIX_RAINDROPS
            return false;
        case RGBM_JELLYBEAN_RAINDROPS:
            #ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_JELLYBEAN_RAINDROPS);
            }
            #endif // ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
            return false;
        case RGBM_HUE_BREATHING:
            #ifdef ENABLE_RGB_MATRIX_HUE_BREATHING
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_HUE_BREATHING);
            }
            #endif // ENABLE_RGB_MATRIX_HUE_BREATHING
            return false;
        case RGBM_HUE_PENDULUM:
            #ifdef ENABLE_RGB_MATRIX_HUE_PENDULUM
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_HUE_PENDULUM);
            }
            #endif // ENABLE_RGB_MATRIX_HUE_PENDULUM
            return false;
        case RGBM_HUE_WAVE:
            #ifdef ENABLE_RGB_MATRIX_HUE_WAVE
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_HUE_WAVE);
            }
            #endif // ENABLE_RGB_MATRIX_HUE_WAVE
            return false;
        case RGBM_PIXEL_RAIN:
            #ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_PIXEL_RAIN);
            }
            #endif // ENABLE_RGB_MATRIX_PIXEL_RAIN
            return false;
        case RGBM_PIXEL_FLOW:
            #ifdef ENABLE_RGB_MATRIX_PIXEL_FLOW
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_PIXEL_FLOW);
            }
            #endif // ENABLE_RGB_MATRIX_PIXEL_FLOW
            return false;
        case RGBM_PIXEL_FRACTAL:
            #ifdef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_PIXEL_FRACTAL);
            }
            #endif // ENABLE_RGB_MATRIX_PIXEL_FRACTAL
            return false;
        case RGBM_TYPING_HEATMAP:
            #ifdef ENABLE_RGB_MATRIX_TYPING_HEATMAP
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
            }
            #endif // ENABLE_RGB_MATRIX_TYPING_HEATMAP
            return false;
        case RGBM_DIGITAL_RAIN:
            #ifdef ENABLE_RGB_MATRIX_DIGITAL_RAIN
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_DIGITAL_RAIN);
            }
            #endif // ENABLE_RGB_MATRIX_DIGITAL_RAIN
            return false;
        case RGBM_SOLID_REACTIVE_SIMPLE:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
            return false;
        case RGBM_SOLID_REACTIVE:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE
            return false;
        case RGBM_SOLID_REACTIVE_WIDE:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
            return false;
        case RGBM_SOLID_REACTIVE_MULTIWIDE:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
            return false;
        case RGBM_SOLID_REACTIVE_CROSS:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_CROSS);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
            return false;
        case RGBM_SOLID_REACTIVE_MULTICROSS:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTICROSS);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
            return false;
        case RGBM_SOLID_REACTIVE_NEXUS:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_NEXUS);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
            return false;
        case RGBM_SOLID_REACTIVE_MULTINEXUS:
            #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
            return false;
        case RGBM_SPLASH:
            #ifdef ENABLE_RGB_MATRIX_SPLASH
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SPLASH);
            }
            #endif // ENABLE_RGB_MATRIX_SPLASH
            return false;
        case RGBM_MULTISPLASH:
            #ifdef ENABLE_RGB_MATRIX_MULTISPLASH
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
            }
            #endif // ENABLE_RGB_MATRIX_MULTISPLASH
            return false;
        case RGBM_SOLID_SPLASH:
            #ifdef ENABLE_RGB_MATRIX_SOLID_SPLASH
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_SPLASH);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_SPLASH
            return false;
        case RGBM_SOLID_MULTISPLASH:
            #ifdef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
            }
            #endif // ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
            return false;
        case RGBM_STARLIGHT:
            #ifdef ENABLE_RGB_MATRIX_STARLIGHT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_STARLIGHT);
            }
            #endif // ENABLE_RGB_MATRIX_STARLIGHT
            return false;
        case RGBM_STARLIGHT_DUAL_SAT:
            #ifdef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_STARLIGHT_DUAL_SAT);
            }
            #endif // ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
            return false;
        case RGBM_STARLIGHT_DUAL_HUE:
            #ifdef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_STARLIGHT_DUAL_HUE);
            }
            #endif // ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
            return false;
        case RGBM_RIVERFLOW:
            #ifdef ENABLE_RGB_MATRIX_RIVERFLOW
            #ifndef RGB_TRIGGER_ON_KEYDOWN
            if (!record->event.pressed) {
            #else
            if (record->event.pressed) {
            #endif // RGB_TRIGGER_ON_KEYDOWN
                rgb_matrix_mode(RGB_MATRIX_RIVERFLOW);
            }
            #endif // ENABLE_RGB_MATRIX_RIVERFLOW
            return false;
    }

    return true;
}

#endif // RGB_MATRIX_ENABLE...
