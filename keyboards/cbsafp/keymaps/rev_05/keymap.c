// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
/*** Updates ***
 * add chording for toggling layers
 */

#include <stdint.h>
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
    _FN,
    _FN2,
    _NP,
};

/***** KEY OVERRIDES ******/
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
//const key_override_t escape_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_ENT, KC_ESC);
const key_override_t dollar_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DLR, KC_AMPR);
const key_override_t underscore_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_HASH);

// define all overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]) {
    &delete_key_override,
    //&escape_key_override,
    &dollar_key_override,
    &underscore_key_override,
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
                reset_oneshot_layer();    // clear all one shot layer

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

/*** Combos ***/
const uint16_t PROGMEM num_combo[] = {LT(_NUM,KC_V), LT(_NUM,KC_M), COMBO_END};
const uint16_t PROGMEM fun_combo[] = {LT(_FN,KC_C), LT(_FN,KC_COMM), COMBO_END};

combo_t key_combos[] = {
    COMBO(num_combo, TO(_NUM)),
    COMBO(fun_combo, TO(_FN))
};

/***** KEYMAPS ******/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ,-----------------------------------------,                                      ,-----------------------------------------,
      * | esc  |   1  |   2  |   3  |   4  |   5  |                                      |   6  |   7  |   8  |   9  |   0  |numpad|
      * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
      * |  tab |   Q  |   W  |   E  |   R  |   T  |                                      |   Y  |   U  |   I  |   O  |   P  | caps |
      * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
      * |   _  |   A  |   S  |   D  |   F  |   G  |                                      |   H  |   J  |   K  |   L  |   ;  |   $  |
      * |------+------+------+------+------+------|                                      |------+------+------+------+------+------|
      * |   '  |   Z  |   X  |   C  |   V  |   B  | ,-------------,      ,-------------, |   N  |   M  |   ,  |   .  |   /  |   \  |
      * '-----------------------------------------' |  L4  |  win |      |  alt |  fn  | '-----------------------------------------'
      *                                       ,------,------,------,    ,------,------,------,
      *                                       | nums |  ent | bspc |    | esc  |  spc | base |
      *                                       '------'------'------'    '------'------'------'
      */

	[_BASE] = LAYOUT(
/*R1*/  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_F12,  TO(_NP),
/*R2*/  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CUST_CAPS,
/*R3L*/ KC_UNDS, MT(MOD_LGUI,KC_A), MT(MOD_LALT,KC_S), MT(MOD_LSFT,KC_D), MT(MOD_LCTL,KC_F), KC_G,
/*R3R*/                                          KC_H, MT(MOD_RCTL,KC_J), MT(MOD_RSFT,KC_K), MT(MOD_RALT,KC_L), MT(MOD_RGUI,KC_SCLN), KC_DLR,
/*R4*/  KC_QUOT, KC_Z, KC_X,LT(_FN,KC_C), LT(_NUM,KC_V), KC_B,      KC_N, LT(_NUM,KC_M), LT(_FN,KC_COMM), KC_DOT,  KC_SLSH, KC_BSLS,
/*R5*/         KC_BSPC, KC_ENT,KC_LCTL,KC_LGUI, TO(_NP),                               TO(_FN), KC_RALT,RST_BASE,KC_SPC, KC_ESC
    ),
	[_NUM] = LAYOUT(
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                                    KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
	_______,KC_MINS,KC_PLUS,KC_LCBR,KC_RCBR,KC_EQL,                                  KC_CIRC,KC_LPRN,KC_RPRN,KC_ASTR,_______,_______,
	_______,KC_EXLM,KC_AT,  KC_LBRC,KC_RBRC,KC_PERC,                                 KC_GRV, KC_TILD,_______,_______,_______,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    ),
	[_FN] = LAYOUT(
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                                   KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, _______,
	_______,_______,KC_LSFT,KC_MS_U,KC_LCTL,_______,                                 KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,_______,_______,
	_______,_______,KC_MS_L,KC_MS_D,KC_MS_R,KC_F11,                                  KC_F12,KC_BTN1,KC_BTN2,KC_BTN3,MO(_FN2),_______,
	        _______,_______,_______,_______,KC_LALT,                                 _______,_______,_______,_______,_______
    ),
	[_FN2] = LAYOUT(
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,_______,KC_WH_U,_______,_______,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,KC_WH_L,KC_WH_D,KC_WH_R,_______,                                 _______,_______,_______,_______,_______,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    ),
	[_NP] = LAYOUT(
	_______,_______,_______,_______,_______,KC_PSLS,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PAST,                                 _______,_______,_______,_______,_______,_______,
	_______,KC_KP_0,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_PMNS,                                 _______,_______,_______,_______,_______,_______,
	_______,_______,KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_PPLS,                                 _______,_______,_______,_______,_______,_______,
	        _______,_______,_______,_______,_______,                                 _______,_______,_______,_______,_______
    )
};

/* Handedness*/
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
             'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R'
    );
