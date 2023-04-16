// clang-format on

/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
  Customizations in this keymap:
    PrtSc button (to left of rotary dial) is now Delete
    R1 is now Home
    R2 is now PgUp
    R3 is now PgDn
    R4 is now End
    FN-R1 is now PrtSc
    FN-R2 is now Num Lock
    FN-R3 is now Scroll Lock
    FN-R4 is now Insert
    TAP-LCTRL is now previous desktop
    TAP-RCTRL is now next desktop
*/

#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _FUNCTION 1
#define _PROG 2

// Tap termination timer
#define TAPPING_TERM 200

// Macro tap detection timers
uint16_t lctl_timer;
uint16_t rctl_timer;

// Custom Keycodes
enum custom_keycodes {
    PREV_DESKTOP = SAFE_RANGE,
    NEXT_DESKTOP,
    CMD_SPC,
    CMD_SNIP
};

// Macro send strings
#define SS_PREV_DESKTOP SS_LCTL(SS_LGUI(SS_TAP(X_LEFT)))
#define SS_NEXT_DESKTOP SS_LCTL(SS_LGUI(SS_TAP(X_RIGHT)))
#define SS_CMD_SPACE    SS_LCMD(" ")
#define SS_MAC_SCRSNIP  SS_LCMD(SS_LSFT(SS_LCTL("4")))

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC          F1           F2           F3           F4           F5           F6           F7           F8           F9           F10          F11          F12	         Del                       Rotary(Mute)
//      ~            1            2            3            4            5            6            7            8            9            0             -           (=)	         BackSpc                   Home
//      Tab          Q            W            E            R            T            Y            U            I            O            P            [            ]            \                         PgUp
//      Caps         A            S            D            F            G            H            J            K            L            ;            "                         Enter                     PgDn
//      Sh_L                      Z            X            C            V            B            N            M            ,            .            ?                         Sh_R         Up           End
//      Ct_L         Win_L        Alt_L                                               SPACE                                               Alt_R        FN           Ct_R         Left         Down         Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.


    [_DEFAULT ] = LAYOUT( // 0
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_DEL,                   KC_MUTE,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_MINS,     KC_EQL,      KC_BSPC,                  KC_HOME,
        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_LBRC,     KC_RBRC,     KC_BSLS,                  KC_PGUP,
        KC_LCTL,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,                  KC_ENT,                   KC_PGDN,
        KC_LSFT,                  KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,                  KC_RSFT,     KC_UP,       KC_END,
        CMD_SPC,     KC_LALT,     KC_LCMD,                                            KC_SPC,                                             KC_RCMD,     KC_RALT,     MO(1),       KC_LEFT,     KC_DOWN,     KC_RGHT
    ),

    [_FUNCTION] = LAYOUT( // 1
        KC_ESC,      KC_F1,       KC_F2,       KC_MCTL,     KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      CMD_SNIP,                 KC_MUTE,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_MINS,     KC_EQL,      KC_BSPC,                  KC_PSCR,
        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_LBRC,     KC_RBRC,     QK_BOOT,                  KC_NUM,
        KC_LCTL,     KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,                  KC_ENT,                   KC_SCRL,
        KC_LSFT,                  KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        NK_TOGG,     KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,                  KC_RSFT,     KC_UP,       KC_INS,
        CMD_SPC,     KC_LALT,     KC_LCMD,                                            KC_SPC,                                             KC_RCMD,     KC_RALT,     MO(1),       KC_LEFT,     KC_DOWN,     KC_RGHT
    )
};

void rgb_set_custom_keys(void) {

  // from gmmk/pro/ansi/ansi.c - map keys to LED numbers

  // F1-12, Home, End, PgUp, PgDn, Del are blue
  int functions[17] = {6, 12, 18, 23, 28, 34, 39, 44, 50, 56, 61, 66, 69, 72, 75, 82, 86 };
  for (int i = 0; i < 17; i++) { rgb_matrix_set_color(functions[i], RGB_BLUE); }

  // Tab, Enter, Space, modifiers are blue
  int modsandthings[12] = {0, 2, 3, 11, 33, 49, 96, 4, 5, 17, 55, 90};
  for (int i = 0; i < 12; i++) { rgb_matrix_set_color(modsandthings[i], RGB_BLUE); }

  // Fn is red
  int reds[1] = {65};
  for (int i = 0; i < 1; i++) { rgb_matrix_set_color(reds[i], RGB_RED); }

  // arrows are blue
  int arrows[4] = {79, 94, 95, 97};
  for (int i = 0; i < 4; i++) { rgb_matrix_set_color(arrows[i], RGB_BLUE); }

  // special or macro keys are yellow
  int special[1] = {5};
  for (int i = 0; i < 1; i++) { rgb_matrix_set_color(special[i], RGB_YELLOW); }

}

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
        case _DEFAULT:
            rgb_matrix_set_color_all(RGB_WHITE); //Light up all the keys in white
            rgb_set_custom_keys();
            break;
        case _FUNCTION:
            rgb_matrix_set_color_all(RGB_WHITE); //Light up all the keys in white
            rgb_set_custom_keys();

            int layer_overrides[9] = { 5, 18, 38, 69, 72, 75, 82, 86, 93 };
            for (int i = 0; i < 9; i++) { rgb_matrix_set_color(layer_overrides[i], RGB_GREEN); }
            break;
    }

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case CMD_SPC:
        if (record->event.pressed) {
            SEND_STRING(SS_CMD_SPACE);
            return false;
        }
    case CMD_SNIP:
        if (record->event.pressed) {
            SEND_STRING(SS_MAC_SCRSNIP);
            return false;
        }
    case PREV_DESKTOP:
        if (record->event.pressed) {
            // Activate LCTL
            lctl_timer = timer_read();
            SEND_STRING(SS_DOWN(X_LCTL));
        } else {
            // Deactivate LCTL
            SEND_STRING(SS_UP(X_LCTL));

            // If the action was a tap
            if (timer_elapsed(lctl_timer) < TAPPING_TERM) {
                SEND_STRING(SS_PREV_DESKTOP);
            }
        }
        return false;

    case NEXT_DESKTOP:
        if (record->event.pressed) {
            // Activate RCTL
            rctl_timer = timer_read();
            SEND_STRING(SS_DOWN(X_RCTL));
        } else {
            // Deactivate RCTL
            SEND_STRING(SS_UP(X_RCTL));

            // If the action was a tap
            if (timer_elapsed(rctl_timer) < TAPPING_TERM) {
                SEND_STRING(SS_NEXT_DESKTOP);
            }
        }
        return false;
  }

  return true;
}


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}
#endif // ENCODER_ENABLE

