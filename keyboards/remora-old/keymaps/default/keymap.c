// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/***** STATUS VARS ******/
static bool caps_state = false;

/***** ENUMS ******/
enum custom_keycodes {
    RST_BASE = SAFE_RANGE,
    CUST_CAPS,
};

enum layer_names {
    _BASE,
    _NUM,
    _NP,
    _FN,
};

/***** KEY OVERRIDES ******/
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t escape_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_ENT, KC_ESC);

// define all overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]) {
    &delete_key_override,
    &escape_key_override,
    NULL //null terminate the array of overrides
};

/***** MACROS ******/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case RST_BASE:
            if(record->event.pressed) {
                // when RST_BASE is pressed
                clear_keyboard();        // clear all keys and mods
                clear_oneshot_mods();    // clear all one shot keys

                if(caps_state) { // disable caps
                    caps_state = false;
                    register_code(KC_CAPS);
                    unregister_code(KC_CAPS);
                }

                layer_move(_BASE);
            }
            else {
                // do nothing when key is released
            }
            break;

        case CUST_CAPS:   // caps lock that allows for caps state tracking
        if(record->event.pressed) {
                if(caps_state) { caps_state = false; } // flip caps state
                else { caps_state = true; } // flip caps state

                // register caps press
                register_code(KC_CAPS);
            }
            else {
                unregister_code(KC_CAPS);
            }
            break;

    }
    return true;
};

/***** KEYMAPS ******/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ,-----------------------------------------,                                      ,-----------------------------------------,
      * | esc  |      |      |      |      |      |                                      |      |      |      |      |      |      |
      * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
      * |      |      |      |      |      |      |                                      |      |      |      |      |      |      |
      * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
      * |      |      |      |      |      |      |                                      |      |      |      |      |      |      |
      * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
      * |      |      |      |      |      |      | ,-------------,      ,-------------, |      |      |      |      |      |      |
      * '-----------------------------------------' |      |      |      |      |      | '-----------------------------------------'
      *                                       ,------,------,------,    ,------,------,------,
      *                                       |      |      |      |    |      |      |      |
      *                                       '------'------'------'    '------'------'------'
      */

	[_BASE] = LAYOUT(
/*R1*/  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TO(_NP),
/*R2*/  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CUST_CAPS,
/*R3L*/ KC_UNDS, MT(MOD_LGUI,KC_A), MT(MOD_LALT,KC_S), MT(MOD_LSFT,KC_D), MT(MOD_LCTL,KC_F), KC_G,
/*R3R*/                                          KC_H, MT(MOD_RCTL,KC_J), MT(MOD_RSFT,KC_K), MT(MOD_RALT,KC_L), MT(MOD_RGUI,KC_SCLN), KC_DLR,
/*R4*/  KC_QUOT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
/*R5*/        KC_BSPC, KC_ENT,  TO(_NUM),KC_LGUI, KC_LALT,                               KC_RALT, TO(_FN),RST_BASE,KC_SPC, OSM(MOD_RSFT)
    ),
	[_NUM] = LAYOUT(
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
	_______,KC_PLUS,MT(MOD_LALT,KC_EQL), MT(MOD_LSFT,KC_MINS),MT(MOD_LCTL,KC_LBRC),KC_RBRC,
                                              KC_LEFT,MT(MOD_RCTL,KC_DOWN),MT(MOD_RSFT,KC_UP),  MT(MOD_RALT,KC_RGHT),KC_AMPR,_______,
	_______,KC_EXLM,KC_AT,KC_GRV, KC_LCBR,KC_RCBR,                                   KC_HOME,KC_END, KC_LPRN,KC_RPRN,KC_CIRC,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    ),
	[_NP] = LAYOUT(
	_______,_______,_______,_______,_______,KC_PSLS,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,KC_P7,  KC_P8,  KC_P9,  KC_PAST,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_P0,  KC_P4,  KC_P5,  KC_P6,  KC_PMNS,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,KC_P1,  KC_P2,  KC_P3,  KC_PPLS,                                 _______,_______,_______,_______,_______,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    ),
	[_FN] = LAYOUT(
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                                   KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,
	_______,_______,_______,_______,_______,KC_F11,                                  KC_F12,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    )
};
