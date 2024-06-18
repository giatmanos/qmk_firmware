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

enum sofle_layers {
    _QWERTY,
    _NUMS,
    _SYMB,
    _NPAD
};

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  SFT_ALT_TAB
};

// Tap Dance declarations
enum {
    TD_SFT_CTRL,
    TD_CTRL_SFT,
};


// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_RCTL),
    [TD_CTRL_SFT] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LSFT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_DEL,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,    KC_MPLY,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
               KC_LGUI, KC_LALT,MO(_NUMS),TD(TD_SFT_CTRL),   KC_ENT,   KC_SPC, TD(TD_CTRL_SFT),  MO(_SYMB), KC_LALT, TG(_NPAD)
),
[_NUMS] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS, KC_PSCR, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
           KC_LGUI, XXXXXXX, _______, G(C(KC_LEFT)), G(C(KC_RIGHT)),     KC_SPC, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
),
[_SYMB] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,    KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_HOME,                      KC_END , KC_EQL , XXXXXXX, KC_LPRN, KC_RPRN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_PLUS, XXXXXXX, KC_LCBR, KC_RCBR, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,  KC_ENT,    LCA(KC_LEFT), LCA(KC_RIGHT), _______, XXXXXXX, XXXXXXX
),
[_NPAD] = LAYOUT(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_NUM, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2,    KC_BTN1,KC_KP_0, KC_PDOT, XXXXXXX, TO(0)
),
};

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
    case KC_WH_U:
        {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool scroll_left_registered;
            if (record->event.pressed)
            {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_WH_L);
                    // Update the boolean variable to reflect the status of KC_DEL
                    scroll_left_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            }
            else
            { // on release of KC_WH_D
                if (scroll_left_registered) {
                    unregister_code(KC_WH_L);
                    scroll_left_registered = false;
                    return false;
                }
            }
            return true;
        }
    case KC_WH_D:
        {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool scroll_right_registered;
            if (record->event.pressed)
            {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_WH_R);
                    // Update the boolean variable to reflect the status of KC_DEL
                    scroll_right_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            }
            else
            { // on release of KC_WH_D
                if (scroll_right_registered) {
                    unregister_code(KC_WH_R);
                    scroll_right_registered = false;
                    return false;
                }
            }
            return true;
        }
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
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code(KC_LSFT);
            register_code(KC_TAB);
        } else {
            unregister_code(KC_LSFT);
            unregister_code(KC_TAB);
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
    [_QWERTY] = { ENCODER_CCW_CW(SFT_ALT_TAB, ALT_TAB), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_NUMS]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(C(KC_Y), C(KC_E)) },
    [_SYMB]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(_______, _______) },
    [_NPAD]  = { ENCODER_CCW_CW(KC_MS_U, KC_MS_D), ENCODER_CCW_CW(KC_MS_L, KC_MS_R) },
};
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master())
    {
        return OLED_ROTATION_0; // flips the display 180 degrees if offhand
    }
    else
    {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_secondary(void) {
    if (host_keyboard_led_state().num_lock)
    {
        oled_write_ln_P(PSTR("Num+"), false);
    }
    else
    {
        oled_write_ln_P(PSTR("Num-"), false);
    }
    oled_write_ln_P(PSTR("\n\n"), false);
    if (host_keyboard_led_state().caps_lock)
    {
        oled_write_ln_P(PSTR("Caps+"), false);
    }
    else
    {
        oled_write_ln_P(PSTR("Caps-"), false);
    }
    oled_write_ln_P(PSTR("\n\n"), false);
    if (host_keyboard_led_state().scroll_lock)
    {
        oled_write_ln_P(PSTR("Scrl+"), false);
    }
    else
    {
        oled_write_ln_P(PSTR("Scrl-"), false);
    }
}

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR("Nums"), false);
            break;
        case _SYMB:
            oled_write_ln_P(PSTR("Symb"), false);
            break;
        case _NPAD:
            oled_write_ln_P(PSTR("NumPad"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

char     key_name = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    // save the row and column (useful even if we can't find a keycode to show)
    last_row = record->event.key.row;
    last_col = record->event.key.col;

    key_name     = ' ';
    last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else {
            keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    key_name = pgm_read_byte(&code_to_name[keycode]);
}

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char)
        ++depad_str;
    return depad_str;
}

static void oled_render_keylog(void) {
    oled_write_char('0' + last_row, false);
    oled_write_P(PSTR("x"), false);
    oled_write_char('0' + last_col, false);
    oled_write_P(PSTR(", k"), false);
    const char *last_keycode_str = get_u16_str(last_keycode, ' ');
    oled_write(depad_str(last_keycode_str, ' '), false);
    oled_write_P(PSTR(":"), false);
    oled_write_char(key_name, false);
}

bool oled_task_kb(void) {
    if (is_keyboard_master()) {
        oled_clear();
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_secondary();
    }
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return process_record_user(keycode, record);
}
#endif // OLED_ENABLE
