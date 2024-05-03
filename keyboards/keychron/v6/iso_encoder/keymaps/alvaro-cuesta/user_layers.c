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

#include "action_layer.h"

#if defined(DIP_SWITCH_ENABLE)

#define USER_DEFAULT_MAC_LAYER 0
#define USER_DEFAULT_WIN_LAYER 3

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
#    if defined(OS_SWITCH_REVERT)
        default_layer_set(1UL << (!active ? USER_DEFAULT_WIN_LAYER : USER_DEFAULT_MAC_LAYER));
#    else
        default_layer_set(1UL << (active ? USER_DEFAULT_WIN_LAYER : USER_DEFAULT_MAC_LAYER));
#    endif
    }

    // This is a full override of the functionality in v6.c
    // Needed so that Win default layer is 3 and we can have 6 layers in total
    return false;
}

#endif // DIP_SWITCH_ENABLE
