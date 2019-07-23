/* Copyright 2019 Yuhai Zhang
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

#define _BL 0
#define _FL 1
#define _WIN_DISABLE 2

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT( /* Base */
    KC_A,  KC_1,  KC_H, \
    MO(_FL),  TG(_WIN_DISABLE),  KC_LGUI   \
  ),
  [_FL] = LAYOUT( /* Fn */
    KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP, \
    KC_TRNS,  KC_TRNS,  KC_LGUI   \
  ),
  [_WIN_DISABLE] = LAYOUT( /* Win_Disable */
    KC_TRNS,  KC_TRNS,  KC_TRNS, \
    KC_TRNS,  KC_TRNS,  KC_NO   \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
    case KC_A:
      if (record->event.pressed) {
        // when keycode KC_A is pressed
        writePinHigh(B3);
      } else {
        // when keycode KC_A is released
      }
      break;
    case KC_1:
      if (record->event.pressed) {
        // when keycode KC_1 is pressed
        writePinLow(B3);
      } else {
        // when keycode KC_1 is released
      }
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _WIN_DISABLE:
        writePinHigh(C3);
        break;
    default: //  for any other layers, or the default layer
        writePinLow(C3);
        break;
    }
  return state;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        writePinHigh(C0);
    } else {
        writePinLow(C0);
    }
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinHigh(C1);
    } else {
        writePinLow(C1);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinHigh(C2);
    } else {
        writePinLow(C2);
    }
}
