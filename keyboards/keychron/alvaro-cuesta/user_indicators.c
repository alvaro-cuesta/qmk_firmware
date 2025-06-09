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
#include "raw_hid.h"
#include "rgb_matrix.h"

// TODO: If Via is not enabled maybe instead manually handle `raw_hid_receive`
#if defined(VIA_ENABLE) && defined(DISCORD_MUTE_LED_INDEX)
#define DISCORD_MUTE_LED_ENABLED
#endif // VIA_ENABLE && DISCORD_MUTE_LED_INDEX

#if defined(VIA_ENABLE) && defined(DISCORD_DEAFEN_LED_INDEX)
#define DISCORD_DEAFEN_LED_ENABLED
#endif // VIA_ENABLE && DISCORD_DEAFEN_LED_INDEX

#if defined(DISCORD_MUTE_LED_ENABLED) || defined(DISCORD_DEAFEN_LED_ENABLED)
enum custom_indicator_status {
    indicator_status_unlit,
    indicator_status_lit_white,
    indicator_status_lit_red
};

#define DISCORD_INDICATOR_TIMEOUT 5000 // 5 seconds
#define DISCORD_INDICATOR_TIMER_DISABLED 0

#endif // DISCORD_MUTE_LED_ENABLED || DISCORD_DEAFEN_LED_ENABLED

#define define_custom_indicator(status, timer) \
    enum custom_indicator_status status = indicator_status_unlit; \
    static uint32_t timer = DISCORD_INDICATOR_TIMER_DISABLED;

#if defined(DISCORD_MUTE_LED_ENABLED)
define_custom_indicator(discord_mute_status, discord_mute_timer)
#endif // DISCORD_MUTE_LED_ENABLED

#if defined(DISCORD_DEAFEN_LED_ENABLED)
define_custom_indicator(discord_deafen_status, discord_deafen_timer)
#endif // DISCORD_DEAFEN_LED_ENABLED

#if !defined(FORCE_TURN_OFF_INDICATORS)
#define handle_normal_indicator_led(led_index, value) \
    if (value) { \
        RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 255,255, 255); \
    } else { \
        if (!rgb_matrix_get_flags()) { \
            RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 0, 0, 0); \
        } \
    }
#else
#define handle_normal_indicator_led(led_index, value) \
    if (value) { \
        RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 255,255, 255); \
    } else { \
        RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 0, 0, 0); \
    }
#endif // FORCE_TURN_OFF_INDICATORS

#if !defined(FORCE_TURN_OFF_INDICATORS)
#define handle_custom_indicator_led(led_index, status, timer) \
    switch (status) { \
        case indicator_status_lit_white: \
            RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 255, 255, 255); \
            break; \
        case indicator_status_lit_red: \
            RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 255, 0, 0); \
            break; \
        case indicator_status_unlit: \
            if (!rgb_matrix_get_flags()) { \
                RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 0, 0, 0); \
            } \
            break; \
    } \
    if ( \
        status != indicator_status_unlit \
        && timer != DISCORD_INDICATOR_TIMER_DISABLED \
        && timer_elapsed32(timer) > DISCORD_INDICATOR_TIMEOUT \
    ) { \
        status = indicator_status_unlit; \
        timer = DISCORD_INDICATOR_TIMER_DISABLED; \
    }
#else
#define handle_custom_indicator_led(led_index, status, timer) \
    switch (status) { \
        case indicator_status_lit_white: \
            RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 255, 255, 255); \
            break; \
        case indicator_status_lit_red: \
            RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 255, 0, 0); \
            break; \
        case indicator_status_unlit: \
            RGB_MATRIX_INDICATOR_SET_COLOR(led_index, 0, 0, 0); \
            break; \
    } \
    if ( \
        status != indicator_status_unlit \
        && timer != DISCORD_INDICATOR_TIMER_DISABLED \
        && timer_elapsed32(timer) > DISCORD_INDICATOR_TIMEOUT \
    ) { \
        status = indicator_status_unlit; \
        timer = DISCORD_INDICATOR_TIMER_DISABLED; \
    }
#endif // FORCE_TURN_OFF_INDICATORS

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX) || defined(NKRO_LED_INDEX) || defined(DISCORD_MUTE_LED_ENABLED) || defined(DISCORD_DEAFEN_LED_ENABLED))

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    #if defined(CAPS_LOCK_LED_INDEX)
    handle_normal_indicator_led(CAPS_LOCK_LED_INDEX, host_keyboard_led_state().caps_lock);
    #endif // CAPS_LOCK_LED_INDEX

    #if defined(NUM_LOCK_LED_INDEX)
    handle_normal_indicator_led(NUM_LOCK_LED_INDEX, host_keyboard_led_state().num_lock);
    #endif // NUM_LOCK_LED_INDEX

    #if defined(SCROLL_LOCK_LED_INDEX)
    handle_normal_indicator_led(SCROLL_LOCK_LED_INDEX, host_keyboard_led_state().scroll_lock);
    #endif // SCROLL_LOCK_LED_INDEX

    #if defined(NKRO_LED_INDEX)
    handle_normal_indicator_led(NKRO_LED_INDEX, keymap_config.nkro);
    #endif // NKRO_LED_INDEX

    #if defined(DISCORD_MUTE_LED_ENABLED)
    handle_custom_indicator_led(DISCORD_MUTE_LED_INDEX, discord_mute_status, discord_mute_timer);
    #endif // DISCORD_MUTE_LED_ENABLED

    #if defined(DISCORD_DEAFEN_LED_ENABLED)
    handle_custom_indicator_led(DISCORD_DEAFEN_LED_INDEX, discord_deafen_status, discord_deafen_timer);
    #endif // DISCORD_DEAFEN_LED_ENABLED

    // We've overriden the default behavior so no need to go back to KB
    return false;
}

#endif // RGB_MATRIX_ENABLE...

#define handle_custom_indicator_message(status, timer) \
    status = command_data[1]; \
    timer = timer_read32();

#if defined(DISCORD_MUTE_LED_ENABLED) || defined(DISCORD_DEAFEN_LED_ENABLED)

enum user_host_indicator_id {
    discord_mute,
    discord_deafen
};

enum user_via_command_id {
    // I didn't want to overload the id_custom_* commands from Via so I took the liberty of defining my own command id
    // in a currently-empty space of the enum -- I'm a naughty boy
    id_has_custom_indicators = 0xE0,
    id_set_custom_indicator
};

bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id   = &(data[0]);
    uint8_t *command_data = &(data[1]);

    switch (*command_id) {
        case id_has_custom_indicators:
            command_data[0] = 1;
            raw_hid_send(data, length);
            return true;
        case id_set_custom_indicator:
            switch (command_data[0]) {
                #if defined(DISCORD_MUTE_LED_ENABLED)
                case discord_mute:
                    handle_custom_indicator_message(discord_mute_status, discord_mute_timer)
                    break;
                #endif // DISCORD_MUTE_LED_ENABLED
                #if defined(DISCORD_DEAFEN_LED_ENABLED)
                case discord_deafen:
                    handle_custom_indicator_message(discord_deafen_status, discord_deafen_timer)
                    break;
                #endif // DISCORD_DEAFEN_LED_ENABLED
            }
            // We don't even `raw_hid_send` here unlike what Via expects us to do -- naughty indeed!
            // We just assume that these commands are unidirectional and broadcast-like
            // For unknown indicators we do nothing
            return true;
    }

    return false;
}

#endif // DISCORD_MUTE_LED_ENABLED || DISCORD_DEAFEN_LED_ENABLED
