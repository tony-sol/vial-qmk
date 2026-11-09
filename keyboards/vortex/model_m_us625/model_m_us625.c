// Copyright 2026 Henryk Zaborowski
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

/* Lock indicators:
 * - the RGB LED under LCtrl or Caps Lock (depending on swap_control_capslock state) turns green while caps lock is on.
 * - the RGB LED under Scroll Lock turns blue while scroll lock is on.
 * - the RGB LED under Scroll Lock turns green while num lock is on.
 * - the RGB LED under Scroll Lock turns red while both scroll and num lock are on.
 * It uses the same brightness as the rest of the lighting,
 * but never goes below LOCK_MIN_LEVEL so it stays visible. */
#    define LOCK_MIN_LEVEL 100

static uint8_t lock_level(void) {
    uint8_t level = rgb_matrix_get_val(); // 0..RGB_MATRIX_MAXIMUM_BRIGHTNESS
    return level < LOCK_MIN_LEVEL ? LOCK_MIN_LEVEL : level;
}

/* @todo get Caps/Scroll Lock keys position by their keycodes */
/* Use LED under Ctrl if swap_control_capslock enabled */
static inline uint8_t get_caps_lock_led(void) {
    return keymap_config.swap_control_capslock ? g_led_config.matrix_co[5][0] : g_led_config.matrix_co[3][0];
}

static inline uint8_t get_num_scroll_lock_led(void) {
    return g_led_config.matrix_co[0][14];
}

/* While RGB Matrix is running, draw the indicators on top of the current effect. */
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    led_t   leds                = host_keyboard_led_state();
    uint8_t caps_lock_led       = get_caps_lock_led();
    uint8_t num_scroll_lock_led = get_num_scroll_lock_led();
    uint8_t lvl                 = lock_level();

#    ifdef LOCK_IND_DEBUG
    /* diagnostic build: lock keys are green when the lock is off, so it's visible that this code runs */
    RGB_MATRIX_INDICATOR_SET_COLOR(caps_lock_led, 0, 255, 0);
    RGB_MATRIX_INDICATOR_SET_COLOR(num_scroll_lock_led, 0, 255, 0);
#    endif

    if (leds.caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(caps_lock_led, 0, lvl, 0);
    }

    if (leds.num_lock || leds.scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(num_scroll_lock_led, (leds.num_lock && leds.scroll_lock) ? lvl : 0, (leds.num_lock && !leds.scroll_lock) ? lvl : 0, (!leds.num_lock && leds.scroll_lock) ? lvl : 0);
    }

    return true;
}

/* RGB Matrix skips indicators while the lighting is switched off (RM_TOGG), so in that
 * case draw them here: everything else stays dark, only the lock keys light up. */
void housekeeping_task_kb(void) {
    static uint32_t refresh_timer = 0;
    static bool     drawn         = false;

    if (!rgb_matrix_is_enabled() && !rgb_matrix_get_suspend_state()) {
        led_t leds = host_keyboard_led_state();
        bool  any  = leds.caps_lock || leds.scroll_lock || leds.num_lock;

        // refresh every 100 ms while needed (and once more to clear after locks go off)
        if ((any || drawn) && timer_elapsed32(refresh_timer) >= 100) {
            uint8_t caps_lock_led       = get_caps_lock_led();
            uint8_t num_scroll_lock_led = get_num_scroll_lock_led();
            uint8_t lvl                 = lock_level();
            refresh_timer               = timer_read32();

            rgb_matrix_set_color_all(0, 0, 0);

            if (leds.caps_lock) {
                rgb_matrix_set_color(caps_lock_led, 0, lvl, 0);
            }

            if (leds.num_lock || leds.scroll_lock) {
                rgb_matrix_set_color(num_scroll_lock_led, (leds.num_lock && leds.scroll_lock) ? lvl : 0, (leds.num_lock && !leds.scroll_lock) ? lvl : 0, (!leds.num_lock && leds.scroll_lock) ? lvl : 0);
            }

            rgb_matrix_update_pwm_buffers();
            drawn = any;
        }
    } else {
        drawn = false;
    }

    housekeeping_task_user();
}

#endif // RGB_MATRIX_ENABLE
