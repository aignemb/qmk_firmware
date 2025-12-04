// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        LCTL(KC_C),   LCTL(KC_X),    KC_BSPC,   KC_SPC,   KC_RCTL,   KC_RALT,
                LCTL(KC_V),   KC_ESC,   KC_RSFT,   KC_ENT
    )
};
