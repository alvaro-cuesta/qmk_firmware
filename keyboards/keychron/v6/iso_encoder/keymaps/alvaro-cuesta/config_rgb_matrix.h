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

#pragma once

/* Defaults */
#define RGB_MATRIX_DEFAULT_ON true
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_DEFAULT_HUE 156 // default is 0, this should be a nice blue
#define RGB_MATRIX_DEFAULT_SAT UINT8_MAX - 64 // default is UINT8_MAX, slightly desaturated for a nice glow
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_DEFAULT_SPD UINT8_MAX / 2

/* Step speed */
// Half of the defaults since we use the encoder and can move fast
// Allows more precision
#define RGB_MATRIX_HUE_STEP 4
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 8

/* RGB effects */
/* In enum order, according to quantum/rgb_matrix/animations/rgb_matrix_effects.inc */
// #define    ENABLE_RGB_MATRIX_SOLID_COLOR // Always exists!
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#define    ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define    ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define    ENABLE_RGB_MATRIX_BREATHING
#define    ENABLE_RGB_MATRIX_BAND_SAT
#define    ENABLE_RGB_MATRIX_BAND_VAL
#define    ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define    ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define    ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define    ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define    ENABLE_RGB_MATRIX_CYCLE_ALL
#define    ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define    ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define    ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define    ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define    ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define    ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define    ENABLE_RGB_MATRIX_DUAL_BEACON
#define    ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define    ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#define    ENABLE_RGB_MATRIX_RAINDROPS
#define    ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#define    ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define    ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN // RGB_DIGITAL_RAIN_DROPS
#define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define    ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define    ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#define    ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#define    ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#undef ENABLE_RGB_MATRIX_STARLIGHT
#undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT
#undef ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE
#define    ENABLE_RGB_MATRIX_RIVERFLOW
