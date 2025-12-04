// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        LCTL(KC_C),   KC_BSPC,    LSFT(KC_X),   LSFT(KC_X),   KC_SPC,   KC_RALT,
                LCTL(KC_V),   KC_ESC,   OSM(MOD_RSFT),   KC_ENT
    )
};
