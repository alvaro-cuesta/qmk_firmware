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

#include "quantum.h"
#include "encoder.h"

const uint16_t PROGMEM keymaps[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS];

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[DYNAMIC_KEYMAP_LAYER_COUNT][NUM_ENCODERS][NUM_DIRECTIONS];
#endif
