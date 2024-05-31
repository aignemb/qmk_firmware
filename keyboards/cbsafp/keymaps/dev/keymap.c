// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

	enum layer_names {
		_BASE,
		_NUM,
		_NP,
		_FN,
	};

// sft + bspc --> del
// init var holding binary representation of mod states
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //store current mod state for later use
    mod_state = get_mods();

    switch(keycode) {
    case KC_BSPC:
        {
            // init var that keeps track of delete key status
            static bool delkey_registered;
            if(record->event.pressed) {
                //detect if either shift is pressed
                if(mod_state & MOD_MASK_SHIFT) {
                    //first disable both shifts
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    //update state of bool del
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                }
            }
            else { //on release of bspc
                //in case bspc still being pressed
                if(delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            //let qmk handle bspc outise of shift
            return true;
        }
    }
    return true;
}

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
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_CAPS,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                 KC_BSPC, KC_ENT,  TO(_NUM),KC_LGUI, KC_LALT,                            KC_RALT, TO(_NP),TO(_BASE),KC_SPC,  OSM(MOD_RSFT)
    ),
	[_NUM] = LAYOUT(
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
	_______,_______,KC_EQL,KC_MINS, KC_LBRC,KC_RBRC,                                 KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,_______,_______,
	_______,_______,KC_GRV, KC_BSLS,KC_QUOT,_______,                                 KC_HOME,KC_END, _______,_______,_______,_______,
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
	_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                                   KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    )
};
