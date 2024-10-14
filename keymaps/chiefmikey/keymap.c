#include QMK_KEYBOARD_H
#include "quantum.h"
#include "lib/oled.h"
#include "analog.h"
#include "audio.h"

// Layer definitions
enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

// tap_dance actions
enum {
    B1_B2
};

// Custom keycodes
enum custom_keycodes {
    EMAIL = SAFE_RANGE,
    ZSK,
    ZIFK
};

tap_dance_action_t tap_dance_actions[] = {
    [B1_B2] = ACTION_TAP_DANCE_DOUBLE(KC_MS_BTN1, KC_MS_BTN2),
};

// Key aliases for readability
#define MT_LCTL_GRV    MT(MOD_LCTL, KC_GRV)   // Control when held, Grave when tapped
#define MT_LALT_SPC    MT(MOD_LALT, KC_SPC)   // Alt when held, Space when tapped
#define LT_ADJ_ENT     LT(_ADJUST, KC_ENT)    // Adjust layer when held, Enter when tapped
#define LT_LOWER_SPC   LT(_LOWER, KC_SPC)     // Lower layer when held, Space when tapped
#define LT_RAISE_BSLS  LT(_RAISE, KC_BSLS)    // Raise layer when held, Backslash when tapped

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EMAIL:
            if (record->event.pressed) {
                SEND_STRING("wolfemikl@gmail.com");
            }
            break;

        case ZSK:
            if (record->event.pressed) {
                // PLAY_SONG(ZELDA_SECRET);
            }
            break;

        case ZIFK:
            if (record->event.pressed) {
                // PLAY_SONG(ZELDA_ITEM_FANFARE);
            }
            break;
    }
    return true;
}

// Keymap definition
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _BASE Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Ctrl/`|   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSFT |   Z  |   X  |   C  |   V  |   B  |-------.    ,-------|   N  |   M  |   ,  |   .  |   /  | RSFT |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI |Alt/SPC|Adj/ENT|      /       \      |Adj/ENT|Low/SPC|Rse/BS|
 *                   `----------------------'     '---------''---------------------------'
 */
[_BASE] = LAYOUT(
    KC_ESC,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
    MT_LCTL_GRV,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                                KC_LGUI, MT_LALT_SPC, LT_ADJ_ENT,            LT_ADJ_ENT, LT_LOWER_SPC, LT_RAISE_BSLS
),
/* _LOWER Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |   =  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |   @  |   $  |   [  |   (  |   {  |                    |   }  |   )  |   ]  |   -  |      |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   &  |   #  |   %  |   !  |   +  |-------.    ,-------|   ^  |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |   *  |      |      |      /       \      |      |      |      |
 *                   `----------------------'     '---------''----------------------'
 */
[_LOWER] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                       KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,  _______,
    KC_TAB,  KC_AT,   KC_DLR,  KC_LBRC, KC_LPRN, KC_LCBR,                    KC_RCBR, KC_RPRN, KC_RBRC, KC_MINS, _______, KC_BSLS,
    _______, KC_AMPR, KC_HASH, KC_PERC, KC_EXLM, KC_PLUS,                    KC_CIRC, _______, _______, _______, _______, _______,
                                    KC_ASTR, _______, _______,            _______, _______, _______
),

/* _RAISE Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      | Left | Down |Right |Vol+  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      | Prev |Vol-  | Next |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      |      /       \      |      |      |      |
 *                   `----------------------'     '---------''----------------------'
 */
[_RAISE] = LAYOUT(
    QK_AUDIO_CLICKY_TOGGLE, _______, _______, _______, _______, _______,                   _______, _______, KC_MUTE,   KC_MPLY, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, KC_VOLU, KC_MSEL,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT,
                                    KC_PWR, _______, _______,             _______, _______, _______
),

/* _ADJUST Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      | ZIFK |  ZSK |                    | EMAIL|  Up  |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | Left | Down |Right |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RGBTOG|RGBMOD|RGBRMD|RGBVAI|RGBVAD|RGBHUD|-------.    ,-------|RGBHUI|RGBSAD|RGBSAI|RGBSPI|RGBSPD|RGBTOG|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      |      /       \      |MT_MS_MS|      |      |
 *                   `----------------------'     '---------''----------------------'
 */
[_ADJUST] = LAYOUT(
    QK_BOOTLOADER, _______, _______, _______, ZIFK,    ZSK,                      EMAIL,   _______,   KC_UP, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                  _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    RGB_TOG, RGB_MOD, RGB_RMOD, RGB_VAI, RGB_VAD, RGB_HUD,                RGB_HUI, RGB_SAD, RGB_SAI, RGB_SPI, RGB_SPD, RGB_TOG,
                                _______, _______, _______,             TD(B1_B2), _______, _______
)

};
