// Copyright 2026 Samuele Panzeri
// SPDX-License-Identifier: GPL-2.0-or-later
//
// TEMPORARY matrix-mapping keymap for the custom bottom two rows.
// All finger rows are silenced (KC_NO); only the right-hand bottom cluster
// prints, and each matrix cell prints a unique character so every physical
// key reveals its exact (row, col):
//
//   matrix row 12 (function row + 2 large thumb keys):  1 2 3 4 5 6   (cols 0..5)
//   matrix row 13 (4 small 1u thumb keys):              7 8 9 0 - =   (cols 0..5)
//
// This keymap writes the matrix directly (no LAYOUT macro) so that EVERY
// possible cell is populated, regardless of the real layout.

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  0  L  F-row
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  1  L  numbers
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  2  L  top letters
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  3  L  home
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  4  L  bottom letters
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  5  L  func + large thumb
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  6  L  small thumb
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  7  R  F-row
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  8  R  numbers
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  //  9  R  top letters
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  // 10  R  home
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   },  // 11  R  bottom letters
        { KC_1,  KC_2,  KC_3,  KC_4,  KC_5,    KC_6    },  // 12  R  func + large thumb
        { KC_7,  KC_8,  KC_9,  KC_0,  KC_MINS, KC_EQL  },  // 13  R  small thumb
    }
};
