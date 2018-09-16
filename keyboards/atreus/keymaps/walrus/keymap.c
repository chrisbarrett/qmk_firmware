#include QMK_KEYBOARD_H

// Layer names
#define L_LETTER 0
#define L_SYMBOL 1

// Custom key identifiers
#define LTHUMB  LCTL_T(KC_UP)
#define RTHUMB  LALT_T(KC_DOWN)
#define KC_BOOT RESET

enum custom_keycodes {
  M_COLON = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: letters
   *
   *  :     ,     .     p     y       ||         f    g    c    r    l
   *  a     o     e     u     i       ||         d    h    t    n    s
   *  '     q     j     k     x       ||         b    m    w    v    z
   *  esc  tab  super shift bspc c/up || m/down spc layer  -    /   enter
   */
  [L_LETTER] = LAYOUT(
    M_COLON, KC_COMM, KC_DOT,  KC_P,      KC_Y,                    KC_F,   KC_G,         KC_C,    KC_R,    KC_L,
    KC_A,    KC_O,    KC_E,    KC_U,      KC_I,                    KC_D,   KC_H,         KC_T,    KC_N,    KC_S,
    KC_QUOT, KC_Q,    KC_J,    KC_K,      KC_X,                    KC_B,   KC_M,         KC_W,    KC_V,    KC_Z,
    KC_ESC,  KC_TAB,  KC_LGUI, KC_LSHIFT, KC_BSPC, LTHUMB, RTHUMB, KC_SPC, MO(L_SYMBOL), KC_MINS, KC_SLSH, KC_ENT
  ),

  /* 1: fn with undvorak-ized punctuation
   *
   *  ~    @      ^     $    %        ||       F4    7     8     9    *
   *  !    &      {     (    [        ||       F3    4     5     6    +
   *  \    |      }     )    ]        ||       `     1     2     3    -
   *     insert super   =  bkspc del  || boot  spc   fn    .     0    #
   */
  [L_SYMBOL] = LAYOUT(
    KC_TILD, KC_AT,   KC_CIRC, KC_DOLLAR, KC_PERC,                  KC_F4,   KC_7,    KC_8,   KC_9, KC_ASTR ,
    KC_EXLM, KC_AMPR, KC_LCBR, KC_LPRN,   KC_LBRC,                  KC_F3,   KC_4,    KC_5,   KC_6, KC_PLUS ,
    KC_BSLS, KC_PIPE, KC_RCBR, KC_RPRN,   KC_RBRC,                  KC_GRV,  KC_1,    KC_2,   KC_3, KC_MINS ,
    KC_NO,   KC_INS,  KC_LGUI, KC_EQL,    KC_BSPC, KC_DEL, KC_BOOT, KC_SPC,  KC_TRNS, KC_DOT, KC_0, KC_HASH
  ),
};

void invert_shift_behaviour(uint16_t keycode) {
  if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
    unregister_code(KC_LSFT);
    register_code(keycode);
    unregister_code(keycode);
    register_code(KC_LSFT);
  } else {
    register_code(KC_LSFT);
    register_code(keycode);
    unregister_code(keycode);
    unregister_code(KC_LSFT);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case M_COLON:
        invert_shift_behaviour(KC_SCLN);
        break;
    }
  }
  return true;
};
