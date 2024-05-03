#include QMK_KEYBOARD_H
#include "user_layers.h"
// Do I need these includes, or is the `QMK_KEYBOARD_H` above just not working for me?
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
