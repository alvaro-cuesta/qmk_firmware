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

#include QMK_KEYBOARD_H

#include "keychron_common.h"

#include "quantum.h"
#include "encoder.h"

#include "user_keycodes.h"
#include "user_layers.h"

// Aliases to keep the keymap clean and aligned
#define RGBM_1  RGBM_SOLID_COLOR
#define RGBM_2  RGBM_BREATHING
#define RGBM_3  RGBM_RIVERFLOW
#define RGBM_4  RGBM_BAND_VAL
#define RGBM_5  RGBM_BAND_SAT
#define RGBM_6  RGBM_BAND_PINWHEEL_VAL
#define RGBM_7  RGBM_BAND_PINWHEEL_SAT
#define RGBM_8  RGBM_BAND_SPIRAL_VAL
#define RGBM_9  RGBM_BAND_SPIRAL_SAT
#define RGBM_0  RGBM_GRADIENT_UP_DOWN
#define RGBM_AP RGBM_GRADIENT_LEFT_RIGHT

#define RGBM_Q  RGBM_CYCLE_ALL
#define RGBM_W  RGBM_CYCLE_LEFT_RIGHT
#define RGBM_E  RGBM_CYCLE_UP_DOWN
#define RGBM_R  RGBM_RAINBOW_MOVING_CHEVRON
#define RGBM_T  RGBM_CYCLE_PINWHEEL
#define RGBM_Y  RGBM_CYCLE_SPIRAL
#define RGBM_U  RGBM_DUAL_BEACON
#define RGBM_I  RGBM_RAINBOW_BEACON
#define RGBM_O  RGBM_CYCLE_OUT_IN
#define RGBM_P  XXXXXXX

#define RGBM_A  RGBM_TYPING_HEATMAP
#define RGBM_S  RGBM_SOLID_REACTIVE_SIMPLE
#define RGBM_D  RGBM_SOLID_REACTIVE
#define RGBM_F  RGBM_SOLID_REACTIVE_MULTIWIDE
#define RGBM_G  RGBM_SOLID_REACTIVE_MULTICROSS
#define RGBM_H  RGBM_SOLID_REACTIVE_MULTINEXUS
#define RGBM_J  RGBM_MULTISPLASH
#define RGBM_K  RGBM_SOLID_MULTISPLASH
#define RGBM_L  XXXXXXX

#define RGBM_Z  RGBM_FLOWER_BLOOMING
#define RGBM_X  RGBM_RAINDROPS
#define RGBM_C  RGBM_JELLYBEAN_RAINDROPS
#define RGBM_V  RGBM_PIXEL_RAIN
#define RGBM_B  XXXXXXX

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Mac
    [MAC_BASE] = LAYOUT_tkl_f13_iso(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,     KC_MUTE,        KC_SNAP,  KC_SIRI,  RM_NEXT,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,      KC_BSPC,        KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                     KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,     KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,               KC_RSFT,                  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, MO(MAC_FN1), KC_RCTL,        KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN1] = LAYOUT_tkl_f13_iso(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,      RM_TOGG,        _______,  _______,  KC_PWR,
        _______,  RGBM_1,   RGBM_2,   RGBM_3,   RGBM_4,   RGBM_5,   RGBM_6,   RGBM_7,   RGBM_8,   RGBM_9,   RGBM_0,   RGBM_AP,  _______,     _______,        _______,  _______,  _______,
        RM_TOGG,  RGBM_Q,   RGBM_W,   RGBM_E,   RGBM_R,   RGBM_T,   RGBM_Y,   RGBM_U,   RGBM_I,   RGBM_O,   RGBM_P,   _______,  _______,                     _______,  _______,  _______,
        _______,  RGBM_A,   RGBM_S,   RGBM_D,   RGBM_F,   RGBM_G,   RGBM_H,   RGBM_J,   RGBM_K,   RGBM_L,   _______,  _______,  _______,     _______,
        _______,  RGBM_Z,   RGBM_X,   RGBM_C,   RGBM_V,   RGBM_B,   _______,  NK_TOGG,  RGBE_EF,  RGBE_HU,  RGBE_SA,  RGBE_SP,               _______,                  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,     _______,        _______,  _______,  _______),

    [MAC_FN2] = LAYOUT_tkl_f13_iso(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,        _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,        _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                     _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,               _______,                  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,     _______,        _______,  _______,  _______),

    // Win
    [WIN_BASE] = LAYOUT_tkl_f13_iso(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,      KC_MUTE,        KC_PSCR,  KC_SCRL,  KC_PAUS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,      KC_BSPC,        KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                     KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,     KC_ENT,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,               KC_RSFT,                  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN1), KC_RCTL,        KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN1] = LAYOUT_tkl_f13_iso(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,     RM_TOGG,        _______,  _______,  KC_PWR,
        _______,  RGBM_1,   RGBM_2,   RGBM_3,   RGBM_4,   RGBM_5,   RGBM_6,   RGBM_7,   RGBM_8,   RGBM_9,   RGBM_0,   RGBM_AP,  _______,     _______,        _______,  _______,  _______,
        RM_TOGG,  RGBM_Q,   RGBM_W,   RGBM_E,   RGBM_R,   RGBM_T,   RGBM_Y,   RGBM_U,   RGBM_I,   RGBM_O,   RGBM_P,   _______,  _______,                     _______,  _______,  _______,
        _______,  RGBM_A,   RGBM_S,   RGBM_D,   RGBM_F,   RGBM_G,   RGBM_H,   RGBM_J,   RGBM_K,   RGBM_L,   _______,  _______,  _______,     _______,
        _______,  RGBM_Z,   RGBM_X,   RGBM_C,   RGBM_V,   RGBM_B,   _______,  NK_TOGG,  RGBE_EF,  RGBE_HU,  RGBE_SA,  RGBE_SP,               _______,                  _______,
        _______,  KC_APP,   _______,                                _______,                                _______,  KC_APP,   _______,     _______,        _______,  _______,  _______),

    [WIN_FN2] = LAYOUT_tkl_f13_iso(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,        _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,        _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                     _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,               _______,                  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,     _______,        _______,  _______,  _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN1]  = {ENCODER_CCW_CW(RGBE_DE, RGBE_IN) },
    [MAC_FN2]  = {ENCODER_CCW_CW(_______, _______) },
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN1]  = {ENCODER_CCW_CW(RGBE_DE, RGBE_IN) },
    [WIN_FN2]  = {ENCODER_CCW_CW(_______, _______) }
};
#endif // ENCODER_MAP_ENABLE

// clang-format on
