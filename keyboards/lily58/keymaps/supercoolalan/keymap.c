// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    _ADJUST
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                          KC_LALT,    KC_LGUI, LOWER, KC_SPC,  KC_ENT,   RAISE,   KC_BSPC, KC_RGUI
),
[_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
[_RAISE] = LAYOUT(
  RM_NEXT, RM_PREV, RM_SATU, RM_SATD, RM_VALU, RM_VALD,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   RM_TOGG, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RGB_MATRIX_ENABLE
// LED positions for 70 LEDs (35 per half: 29 keys + 6 underglow)
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index - Left half
        { 0,  1,  2,  3,  4,  5 },
        { 11, 10, 9,  8,  7,  6 },
        { 12, 13, 14, 15, 16, 17 },
        { 23, 22, 21, 20, 19, 18 },
        { NO_LED, NO_LED, 24, 25, 26, 27 },
        // Key Matrix to LED Index - Right half
        { 35, 36, 37, 38, 39, 40 },
        { 46, 45, 44, 43, 42, 41 },
        { 47, 48, 49, 50, 51, 52 },
        { 58, 57, 56, 55, 54, 53 },
        { NO_LED, NO_LED, 59, 60, 61, 62 }
    },
    {
        // LED Index to Physical Position - Left half keys (29)
        {0, 0},   {17, 0},  {34, 0},  {51, 0},  {68, 0},  {85, 0},
        {85, 16}, {68, 16}, {51, 16}, {34, 16}, {17, 16}, {0, 16},
        {0, 32},  {17, 32}, {34, 32}, {51, 32}, {68, 32}, {85, 32},
        {85, 48}, {68, 48}, {51, 48}, {34, 48}, {17, 48}, {0, 48},
        {51, 64}, {68, 64}, {85, 64}, {102, 64}, {102, 48},
        // Left half underglow (6)
        {85, 8}, {51, 8}, {17, 8}, {17, 40}, {51, 40}, {85, 40},
        // Right half keys (29)
        {139, 0},  {156, 0},  {173, 0},  {190, 0},  {207, 0},  {224, 0},
        {224, 16}, {207, 16}, {190, 16}, {173, 16}, {156, 16}, {139, 16},
        {139, 32}, {156, 32}, {173, 32}, {190, 32}, {207, 32}, {224, 32},
        {224, 48}, {207, 48}, {190, 48}, {173, 48}, {156, 48}, {139, 48},
        {173, 64}, {156, 64}, {139, 64}, {122, 64}, {122, 48},
        // Right half underglow (6)
        {139, 8}, {173, 8}, {207, 8}, {207, 40}, {173, 40}, {139, 40}
    },
    {
        // LED Index to Flag
        // Left keys (29)
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4,
        // Left underglow (6)
        2, 2, 2, 2, 2, 2,
        // Right keys (29)
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4,
        // Right underglow (6)
        2, 2, 2, 2, 2, 2
    }
};
#endif
