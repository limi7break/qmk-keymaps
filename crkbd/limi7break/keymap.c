#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _SYMBOL,
    _FNAV,
    _MACRO
};

enum keycodes {
    // Acute accents
    IT_AACT = SAFE_RANGE,
    IT_EACT,
    IT_IACT,
    IT_OACT,
    IT_UACT,

    // Grave accents
    IT_AGRV,
    IT_EGRV,
    IT_IGRV,
    IT_OGRV,
    IT_UGRV,

    // Euro symbol
    IT_EURO,

    // Arrow macros (e.g. =>)
    KC_LTEQ,
    KC_EQLT,
    KC_GTEQ,
    KC_EQGT
};

#define SYMBOL MO(_SYMBOL)
#define FNAV MO(_FNAV)
#define MACRO MO(_MACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, KC_LALT,  SYMBOL,        FNAV,  KC_SPC, KC_RSFT
    ),                                  //`--------------------------'  `--------------------------'
    [_SYMBOL] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC,  KC_GRV, KC_BSLS, KC_LCBR, KC_LBRC, KC_LPRN,                      KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS, KC_PLUS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS,  KC_EQL, KC_PIPE,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_ENT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, KC_LALT, _______,      MACRO,  KC_SPC, KC_RSFT
    ),                                  //`--------------------------'  `--------------------------'
    [_FNAV] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC, KC_F9,  KC_F10,  KC_F11,  KC_F12,   XXXXXXX,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_MUTE,  KC_APP,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_MSTP,  KC_ENT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, KC_LALT,   MACRO,    _______,  KC_SPC, KC_RSFT
    ),                                  //`--------------------------'  `--------------------------'
    [_MACRO] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC, KC_TILD, KC_PIPE, IT_EGRV, XXXXXXX, XXXXXXX,                      XXXXXXX, IT_UGRV, IT_IGRV, IT_OGRV, XXXXXXX, KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, IT_AGRV, XXXXXXX, IT_EACT, XXXXXXX, XXXXXXX,                      XXXXXXX, IT_UACT, IT_IACT, IT_OACT, KC_EQGT, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, IT_AACT, XXXXXXX, IT_EURO, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_CAPS, KC_SCRL,  KC_NUM, RM_TOGG, KC_ENT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, KC_LALT, _______,    _______,  KC_SPC, KC_RSFT
    )                                   //`--------------------------'  `--------------------------'
};

uint8_t mod_state;

void send_altcode(char *n) {
    led_t led_state = host_keyboard_led_state();
    
    // If Num Lock is off, turn it on
    if (!(led_state.num_lock)) {
        tap_code16(KC_NUM);
    }
    
    del_mods(MOD_MASK_SHIFT);
    
    // Send altcode
    register_code(KC_LALT);
    for (int i = 0; i < strlen(n); i++) {
        uint8_t digit = n[i] - '0';
        uint8_t keycode = digit > 0 ? KC_P1 - 1 + digit : KC_P0;
        tap_code(keycode);
    }
    unregister_code(KC_LALT);
    
    set_mods(mod_state);
    
    // If Num Lock was off before, restore it
    if (!(led_state.num_lock)) {
        tap_code16(KC_NUM);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {
        case KC_LTEQ:
            if (record->event.pressed) {
                SEND_STRING("<=");
            }
            return false;
        case KC_EQLT:
            if (record->event.pressed) {
                SEND_STRING("=<");
            }
            return false;
        case KC_GTEQ:
            if (record->event.pressed) {
                SEND_STRING(">=");
            }
            return false;
        case KC_EQGT:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
        case IT_AACT:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0193") : send_altcode("0225");
            }
            return false;
        case IT_EACT:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0201") : send_altcode("0233");
            }
            return false;
        case IT_IACT:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0205") : send_altcode("0237");
            }
            return false;
        case IT_OACT:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0211") : send_altcode("0243");
            }
            return false;
        case IT_UACT:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0218") : send_altcode("0250");
            }
            return false;
        case IT_AGRV:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0192") : send_altcode("0224");
            }
            return false;
        case IT_EGRV:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0200") : send_altcode("0232");
            }
            return false;
        case IT_IGRV:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0204") : send_altcode("0236");
            }
            return false;
        case IT_OGRV:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0210") : send_altcode("0242");
            }
            return false;
        case IT_UGRV:
            if (record->event.pressed) {
                mod_state & MOD_MASK_SHIFT ? send_altcode("0217") : send_altcode("0249");
            }
            return false;
        case IT_EURO:
            if (record->event.pressed) {
                send_altcode("0128");
            }
            return false;
        default:
            return true;
    }
}

#ifdef COMBO_ENABLE
enum combos {
    DF_ESC,
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[] = {
    [DF_ESC] = COMBO(df_combo, KC_ESC),
};
#endif // COMBO_ENABLE

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {
    pointing_device_set_cpi(600);
}

static bool scrolling = false;
static enum mouse_buttons tap_is = MOUSE_BTN1;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _MACRO:
            scrolling = true;
            pointing_device_set_cpi(30);
            tap_is = MOUSE_BTN3;
            break;
        case _FNAV:
            scrolling = true;
            pointing_device_set_cpi(30);
            tap_is = MOUSE_BTN2;
            break;
        default:
            if (scrolling) {
                pointing_device_set_cpi(600);
            }
            scrolling = false;
            tap_is = MOUSE_BTN1;
    }
    return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (mouse_report.buttons & MOUSE_BTN1) {
        if (tap_is != MOUSE_BTN1) {
            mouse_report.buttons &= ~MOUSE_BTN1;
            mouse_report.buttons |= tap_is;
        }
    } else {
        mouse_report.buttons = 0;
    }
    if (scrolling) {
        mouse_report.h = -mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
#endif // POINTING_DEVICE_ENABLE
