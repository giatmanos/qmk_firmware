/* Copyright 2023 Brian Low
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
#include QMK_KEYBOARD_H

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
bool is_sft_alt_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t sft_alt_tab_timer = 0;     // we will be using them soon.

enum sofle_layers {
    _QWERTY,
    _SYMB,
    _RAISE,
    _NPAD
};

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  SFT_ALT_TAB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |Bsp/Dl|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * | Home |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | End  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI |      | LOW  | SFT  | /Enter  /       \Space \  | RCTRL| RAISE| ALT  |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,     KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_HOME,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,   KC_MPLY,KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_END,
                      KC_LGUI,  _______,MO(_SYMB), KC_LSFT, KC_ENT, KC_SPC, KC_RCTL,  MO(_RAISE),KC_RALT, _______
),
/* SYMB
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   -  |   +  |   /  |   *  |   _  |   =  |-------.    ,-------| Left | Down |  Up  | Right|   ;  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |   ^  |   &  |  {   |  [   |   (  |   !  |-------|    |-------|      |   )  |   ]  |   }  |   \  |   $  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |SYMB | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYMB] = LAYOUT(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
  KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_UNDS, KC_EQL,                       KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN, KC_PIPE,
  KC_CIRC,  KC_AMPR, KC_LCBR, KC_LBRC, KC_LPRN, KC_EXLM, _______,       _______, KC_AT, KC_RPRN, KC_RBRC, KC_RCBR, KC_BSLS, KC_DLR,
                     _______, _______, _______, _______, _______,       _______, _______, TG(_NPAD), KC_RALT, _______
),
/* NPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   -  |   +  |   /  |   *  |   _  |   =  |-------.    ,-------| Left | Down |  Up  | Right|   ;  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |   !  |  &   |  {   |  [   |   (  |   ^  |-------|    |-------|   $  |   )  |   ]  |   }  |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |SYMB | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NPAD] = LAYOUT(
  _______,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______,  _______, _______, _______, _______, _______,                     _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______,
  _______,  _______, _______, _______, _______, _______,                     _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_ENT , _______,
  _______,  _______, _______, _______, _______, _______, _______,    _______,_______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
                     _______, _______, _______, _______, _______,    TG(_NPAD),KC_KP_0  , KC_PDOT, _______, _______
),
/* RAISE
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |SYMB | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  _______, _______ , _______ , _______ , _______ , _______,                           _______,  _______  , _______,  _______ ,  _______ ,_______,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                        KC_PGUP,  _______,   KC_UP,  _______, _______, KC_BSPC,
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                       KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_DEL, KC_BSPC,
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,  _______,       _______,  XXXXXXX,  _______, XXXXXXX,  _______,   XXXXXXX, _______,
                    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______
)
};

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }
    break;
    case ALT_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        break;
    case SFT_ALT_TAB:
        if (record->event.pressed) {
            if (!is_sft_alt_tab_active) {
                is_sft_alt_tab_active = true;
                register_code(KC_LALT);
            }
            sft_alt_tab_timer = timer_read();
            register_code(KC_TAB);
            register_code(KC_LSFT);
        } else {
            unregister_code(KC_TAB);
            unregister_code(KC_LSFT);
        }
        break;
    }
    return true;
};


void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(SFT_ALT_TAB, ALT_TAB) },
    [_SYMB]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(C(KC_Y), C(KC_E)) },
    [_NPAD]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_RAISE]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif

#ifdef OLED_ENABLE
static void print_status_narrow(void) {
    oled_clear();
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _SYMB:
            oled_write_P(PSTR("Symb"), false);
            break;
        case _NPAD:
            oled_write_ln_P(PSTR("Num\n"), false);
            oled_write_ln_P(PSTR("Pad"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master())
    {
        return OLED_ROTATION_270;
    }
    else
    {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    }
    else
    {
        if (host_keyboard_led_state().num_lock)
        {
            oled_write_ln_P(PSTR("Num"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("On"), false);
        }
        else
        {
            oled_write_ln_P(PSTR("Num"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("Off"), false);
        }
        oled_write_ln_P(PSTR("\n\n"), false);
        if (host_keyboard_led_state().caps_lock)
        {
            oled_write_ln_P(PSTR("Caps"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("On"), false);
        }
        else
        {
            oled_write_ln_P(PSTR("Caps"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("Off"), false);
        }
        oled_write_ln_P(PSTR("\n\n"), false);
        if (host_keyboard_led_state().scroll_lock)
        {
            oled_write_ln_P(PSTR("Scrl"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("On"), false);
        }
        else
        {
            oled_write_ln_P(PSTR("Scroll"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("Off"), false);
        }
    }
    return false;
}

#endif