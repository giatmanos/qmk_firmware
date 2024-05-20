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
    _SYMB,
    _RAISE,
    _NPAD
};

enum custom_keycodes {          // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  SFT_ALT_TAB
};

// Tap Dance declarations
enum {
    TD_ESC_HOME,
    TD_ESC_END,
    TD_SFT_CTRL,
    TD_CTRL_SFT,
    TD_PRN,
    TD_CBR,
    TD_BRC,
    TD_QUOT_LAYER
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SIGNLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct
{
    bool is_press_action;
    td_state_t state;
} td_tap_t;


// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_HOME),
    [TD_ESC_END] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_END),
    [TD_SFT_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_RCTL),
    [TD_CTRL_SFT] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LSFT),
    [TD_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_CBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
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
 *            | LGUI | LCTRL| SYMB | SFT  | /Enter  /       \Space \  | RCTRL| RAISE| ALT  | SFT  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_QWERTY] = LAYOUT(
    KC_GRV,           KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                   KC_6,     KC_7,     KC_8,    KC_9,    KC_0,        TG(_NPAD),
    KC_DEL,           KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                   KC_Y,     KC_U,     KC_I,    KC_O,    KC_P,        KC_BSPC,
    KC_TAB,           KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                   KC_H,     KC_J,     KC_K,    KC_L,    KC_SCLN,     KC_QUOT,
    TD(TD_ESC_HOME),  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,      KC_MUTE,   KC_MPLY,   KC_N,     KC_M,     KC_COMM, KC_DOT,  KC_SLSH, TD(TD_ESC_END),
                               KC_LGUI, KC_LALT,MO(_SYMB),TD(TD_SFT_CTRL),   KC_ENT,   KC_SPC, TD(TD_CTRL_SFT),  LM(_SYMB, MOD_LSFT),KC_LALT, TG(_RAISE)
),
/* SYMB
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |  +=  |  -_  |      |-------.    ,-------| Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |   ^  |      |      |      |      |      |-------|    |-------|      |  ()  |  {}  |  []  |  \|  |   $  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |SYMB | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_SYMB] = LAYOUT(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL, KC_MINS, XXXXXXX,                               KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
  KC_CIRC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,       XXXXXXX, XXXXXXX, TD(TD_PRN), TD(TD_CBR), TD(TD_BRC), KC_BSLS, KC_DLR,
    LM(_SYMB, MOD_LGUI|MOD_LCTL), LM(_SYMB, MOD_LGUI|MOD_LALT), XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  XXXXXXX,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                          XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, KC_PGUP, KC_F12,
  XXXXXXX, LCTL(KC_Y),  XXXXXXX,  XXXXXXX,  XXXXXXX, KC_CAPS,                       KC_LEFT, KC_DOWN,  KC_UP  ,  KC_RGHT, KC_PGDN, XXXXXXX,
  XXXXXXX,LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,  XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
                    XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN2, KC_BTN1,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______ 
),
[_NPAD] = LAYOUT(
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_NUM, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_BSPC,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_ENT,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS, KC_PAST,
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,KC_KP_0  , KC_PDOT, XXXXXXX, XXXXXXX
),
};

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
td_state_t cur_dance(tap_dance_state_t *state);
void ql_finished(tap_dance_state_t* state, void* user_data);
void ql_reset(tap_dance_state_t* state, void* user_data);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
    case KC_MS_U:
        {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool mouse_up_registered;
            if (record->event.pressed)
            {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_MS_L);
                    // Update the boolean variable to reflect the status of KC_DEL
                    mouse_up_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            }
            else
            { // on release of KC_WH_D
                if (mouse_up_registered) {
                    unregister_code(KC_MS_L);
                    mouse_up_registered = false;
                    return false;
                }
            }
            return true;
        }
    case KC_MS_D:
        {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            static bool mouse_down_registered;
            if (record->event.pressed)
            {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_MS_R);
                    // Update the boolean variable to reflect the status of KC_DEL
                    mouse_down_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            }
            else
            { // on release of KC_WH_D
                if (mouse_down_registered) {
                    unregister_code(KC_MS_R);
                    mouse_down_registered = false;
                    return false;
                }
            }
            return true;
        }
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
    [_SYMB]  = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(C(KC_Y), C(KC_E)) },
    [_NPAD]  = { ENCODER_CCW_CW(KC_MS_U, KC_MS_D), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_RAISE]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(_______, _______) }
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
            oled_write_ln_P(PSTR("Scrl"), false);
            oled_write_ln_P(PSTR("Lock"), false);
            oled_write_ln_P(PSTR("Off"), false);
        }
    }
    return false;
}

#endif