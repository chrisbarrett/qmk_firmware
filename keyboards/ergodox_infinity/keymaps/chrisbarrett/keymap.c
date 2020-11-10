#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   &    |   7  |   5  |  3   |  1   |  9   |  F3  |           |  F4  |  0   |  2   |  4   |  6   |  8   |   F12  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   ;  |   ,  |   .  |   p  |   y  |  ^   |           |  $   |   f  |   g  |   c  |   r  |   l  |   |    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | C,Esc  |   a  |   o  |   e  |   u  |   i  |------|           |------|   d  |   h  |   t  |   n  |  s   | Enter  |
 * |--------+------+------+------+------+------| BkTb |           | Tab  |------+------+------+------+------+--------|
 * |   (    |   '  |   q  |   j  |   k  |   x  |      |           |      |   b  |   m  |   w  |   v  |  z   |   @    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  [   |  {   | Hyper| Meta |  S   |                                       |   S  |  -   |   +  |   /  |  #   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | <Nav | Nav U|       | Nav D| Nav> |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | < Mv |       | Mv > |      |      |
 *                                 |Bkspc |  Up  |------|       |------| Down | SPC  |
 *                                 |      |      | Left |       | Right|      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_1,                KC_2, KC_3,    KC_4,    KC_5,      KC_6,   KC_F3,
        KC_TAB,              KC_Q, KC_W,    KC_E,    KC_R,      KC_T,   LSFT(KC_RBRACKET),
        MT(MOD_LCTL, KC_ESC),KC_A, KC_S,    KC_D,    KC_F,      KC_G,
        KC_5,                KC_Z, KC_X,    KC_C,    KC_V,      KC_B,   LSFT(KC_TAB),
                  KC_2,      KC_3, KC_LGUI, KC_LALT, KC_LSFT,

                                                 LGUI(KC_J), LGUI(KC_K),
                                                             LGUI(LSFT(KC_J)),
                                        KC_BSPC, KC_UP,      KC_LEFT,

        // right hand
        KC_F4,           KC_7,       KC_8,       KC_9,        KC_0,       KC_MINS,        KC_F12,
        KC_GRV,          KC_Y,       KC_U,       KC_I,        KC_O,       KC_P,           KC_PIPE,
                         KC_H,       KC_J,       KC_K,        KC_L,       KC_SCOLON,      KC_ENT,
        KC_TAB,          KC_N,       KC_M,       KC_COMM,     KC_DOT,     KC_SLSH,        KC_RBRACKET,
                                     KC_RSFT,    KC_QUOT,     KC_9,       KC_LBRACKET,    KC_EQL,

        LGUI(KC_L),  LGUI(KC_P),
        LGUI(LSFT(KC_P)),
        KC_RIGHT,    KC_DOWN, KC_SPC
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
