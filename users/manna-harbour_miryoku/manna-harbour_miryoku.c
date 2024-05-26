// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};


// thumb combos

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN3),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif

#ifdef OLED_ENABLE
static const char PROGMEM skyrim_logo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xf8, 0x3c, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x08, 0x3c, 0xf8, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
0xe0, 0xf8, 0xfe, 0xff, 0xff, 0x07, 0x00, 0x3e, 0x3f, 0x1e, 0x9e, 0x9c, 0xf0, 0x60, 0x03, 0xff, 
0xff, 0xff, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x87, 
0xc3, 0xc0, 0xe0, 0xfe, 0xff, 0xff, 0xf3, 0xc1, 0xc1, 0xe0, 0xe0, 0xc3, 0x83, 0xff, 0xff, 0xff, 
0xff, 0xfc, 0xf8, 0x40, 0x00, 0x03, 0x07, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x7f, 0x7f, 
0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x0f, 0x03, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x3f, 0xff, 0xfc, 0xf8, 0xc0, 0xc0, 0xff, 0xff, 0x3f, 
0x1f, 0xf0, 0xf8, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0xe7, 0xff, 0x9f, 0x04, 0x00, 0x00, 0x03, 0x03, 0x03, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00};

static const char PROGMEM fus_ro_dah_logo[] = {0x40, 0xc0, 0xc0, 0x40, 0x78, 0x78, 0x1c, 0xfc, 0xfc, 0x00, 0x80, 0xf8, 0xe0, 0x00, 0x0c, 0x7c, 
0x0c, 0xfc, 0xfc, 0x00, 0x40, 0xc0, 0xc0, 0xfc, 0xfc, 0x00, 0xf8, 0xf8, 0x38, 0x00, 0x00, 0x1f, 
0x07, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x03, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0x0f, 0x00, 0x00, 0x0f, 0x01, 0x1f, 0x0f, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 
0xfc, 0xfc, 0xe0, 0xe0, 0x60, 0xfc, 0xfc, 0x08, 0x00, 0x00, 0x00, 0x04, 0x1c, 0x9c, 0xe4, 0xcc, 
0x3c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x01, 
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x0c, 0x06, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x02, 0x07, 0x03, 0x01, 
0x1f, 0x07, 0x00, 0x00, 0x03, 0x3f, 0x07, 0x18, 0xf8, 0x79, 0x7f, 0x3f, 0x07, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static void print_logo_narrow(void) {
    oled_set_cursor(0, 5);
    oled_write_raw_P(fus_ro_dah_logo, sizeof(fus_ro_dah_logo));
}

static void print_status_narrow(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
    oled_write_raw_P(skyrim_logo, sizeof(skyrim_logo));
    
    oled_set_cursor(0, 8);

    /* Print current layer */
    oled_write("LAYER\n", false);

    oled_set_cursor(0, 10);
    switch (get_highest_layer(layer_state)) {
        case U_BASE:
            oled_write("BASE ", false);
            break;
        case U_NAV:
            oled_write("NAV  ", false);
            break;
        case U_MOUSE:
            oled_write("MOUSE", false);
            break;
        case U_MEDIA:
            oled_write("MEDIA", false);
            break;
        case U_NUM:
            oled_write("NUM  ", false);
            break;
        case U_FUN:
            oled_write("FUN  ", false);
            break;
        case U_SYM:
            oled_write("SYM  ", false);
            break;
        default:
            oled_write("Undef", false);
    }

    uint8_t n = get_current_wpm();
    char    wpm_str[4];
    oled_set_cursor(0, 14);
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + n % 10;
    wpm_str[1] = '0' + (n /= 10) % 10;
    wpm_str[0] = '0' + n / 10;
    oled_write(wpm_str, false);

    oled_set_cursor(0, 15);
    oled_write(" wpm", false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }


bool oled_task_user(void) {
    /* KEYBOARD PET VARIABLES START */

    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    /* KEYBOARD PET VARIABLES END */

    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}

#endif // OLED_ENABLE
