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

#include "quantum_keycodes.h"

enum custom_keycodes_user {
    /* RGB effect control */
    RGBE_IN = SAFE_RANGE,
    RGBE_DE,

    /* RGB effect modifiers */
    // RGBE_VA, -- we don't use this since we want this to be the default non-shifted action
    RGBE_HU,
    RGBE_SA,
    RGBE_SP,
    RGBE_EF,

    /* RGB modes */
    RGBM_SOLID_COLOR,
    RGBM_ALPHAS_MODS,
    RGBM_GRADIENT_UP_DOWN,
    RGBM_GRADIENT_LEFT_RIGHT,
    RGBM_BREATHING,
    RGBM_BAND_SAT,
    RGBM_BAND_VAL,
    RGBM_BAND_PINWHEEL_SAT,
    RGBM_BAND_PINWHEEL_VAL,
    RGBM_BAND_SPIRAL_SAT,
    RGBM_BAND_SPIRAL_VAL,
    RGBM_CYCLE_ALL,
    RGBM_CYCLE_LEFT_RIGHT,
    RGBM_CYCLE_UP_DOWN,
    RGBM_RAINBOW_MOVING_CHEVRON,
    RGBM_CYCLE_OUT_IN,
    RGBM_CYCLE_OUT_IN_DUAL,
    RGBM_CYCLE_PINWHEEL,
    RGBM_CYCLE_SPIRAL,
    RGBM_DUAL_BEACON,
    RGBM_RAINBOW_BEACON,
    RGBM_RAINBOW_PINWHEELS,
    RGBM_FLOWER_BLOOMING,
    RGBM_RAINDROPS,
    RGBM_JELLYBEAN_RAINDROPS,
    RGBM_HUE_BREATHING,
    RGBM_HUE_PENDULUM,
    RGBM_HUE_WAVE,
    RGBM_PIXEL_RAIN,
    RGBM_PIXEL_FLOW,
    RGBM_PIXEL_FRACTAL,
    RGBM_TYPING_HEATMAP,
    RGBM_DIGITAL_RAIN,
    RGBM_SOLID_REACTIVE_SIMPLE,
    RGBM_SOLID_REACTIVE,
    RGBM_SOLID_REACTIVE_WIDE,
    RGBM_SOLID_REACTIVE_MULTIWIDE,
    RGBM_SOLID_REACTIVE_CROSS,
    RGBM_SOLID_REACTIVE_MULTICROSS,
    RGBM_SOLID_REACTIVE_NEXUS,
    RGBM_SOLID_REACTIVE_MULTINEXUS,
    RGBM_SPLASH,
    RGBM_MULTISPLASH,
    RGBM_SOLID_SPLASH,
    RGBM_SOLID_MULTISPLASH,
    RGBM_STARLIGHT,
    RGBM_STARLIGHT_DUAL_SAT,
    RGBM_STARLIGHT_DUAL_HUE,
    RGBM_RIVERFLOW
};
