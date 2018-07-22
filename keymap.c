/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


/*
 * Layout: 59key
 * ,-----------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
 * |-----------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BS  |
 * |-----------------------------------------------------------|
 * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
 * |-----------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
 * |-----------------------------------------------------------|
 * |Ctrl |   |Alt  |           Fn4             |Alt  |   |Fn1  |
 * `-----'   `---------------------------------------'   `-----'
 *
 * Matrix: 12x8
 *    |       0 |       1 |       2 |       3 |       4 |       5 |       6 |       7
 * ---+---------+---------+---------+---------+---------+---------+---------+---------
 *  0 |         | F1      | LCTRL   |         |         |         | RCTRL   |        
 *  1 |         | LSHIFT  |         |         |         |         | RSHIFT  |        
 *  2 |         | Tab     | Grave   | 1       | Q       | A       | Z       |        
 *  3 |         | Cpslck  |         | 2       | W       | S       | X       |        
 *  4 |         |         |         | 3       | E       | D       | C       |        
 *  5 | G       | T       | 5       | 4       | R       | F       | V       | B      
 *  6 |         | Bckspc  |         |         | Key*1   | Bckslsh | Enter   | Space  
 *  7 | H       | Y       | 6       | 7       | U       | J       | M       | N      
 *  8 |         | Rbrckt  | Equal   | 8       | I       | K       | Comma   |
 *  9 |         |         |         | 9       | O       | L       | Dot     |        
 *  A |         | Lbrckt  | Minus   | 0       | P       | Smcolon |         | Slash  
 *  B | LALT    |         |         |         |         |         |         | RALT   
 *  Key*1 This key locates between Equal and Backspace.
 *
 *  Original matrix here: http://geekhack.org/showthread.php?7767-Wireless-Model-M&p=133911&viewfull=1#post133911
 */
#define KEYMAP(K00, K10, K20, K30, K40, K50, K60, K70, K80, K90, K87, K97, KA7, K0A, \
    K13, K01, K11, K21, K31, K41, K51, K61, K71, K81, K91, K95, KA5, KA1, \
    K12, K22, K32, K42, K52, K62, K72, K82, K92, K05, K15, K25, KA6, KA2, \
    K03, K33, K43, K53, K63, K73, K45, K55, K65, K75, K85, K06, K16, \
    K23, K04, K14, K24, K34, K44, K54, K74, K84, K76, K86, K96, K93, K83, \
    K02, K35, K46, K57, K64, K77, K66, K49, KA3, KA4 \
    \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_NO    }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_NO    }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_NO,    KC_NO    }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_NO,    KC_NO    }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_NO,    KC_##K57 }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_NO    }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_##K80, KC_##K81, KC_##K82, KC_##K83, KC_##K84, KC_##K85, KC_##K86, KC_##K87 }, \
    { KC_##K90, KC_##K91, KC_##K92, KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_##K97 }, \
    { KC_##KA0, KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5, KC_##KA6, KC_##KA7 }, \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    0,              // Fn1
    0,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_SLSH,        // Fn2
    KC_SCLN,        // Fn3
    KC_SPC,         // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]| BS  |
     * |-----------------------------------------------------------|
     * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |   |Alt  |           Fn4             |Alt  |   |Fn1  |
     * `-----'   `---------------------------------------'   `-----'
     */
    KEYMAP(
            ESC,    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11,  F12,     EJCT, \
            NUBS,   1,  2,  3,  4,  5,  6,  7,  8,   9,  0,  MINS, EQL,     BSPC, \
            TAB,     Q,  W,  E,  R,  T,  Y,  U,  I,   O,  P,  LBRC, RBRC,  ENTER, \
            CAPS,     A,  S,  D,  F,  G,  H,  J,  K,   L,  SCLN, QUOT,  BSLS,     \
            LSFT, GRV, Z,  X,  C,  V,  B,  N,  M,  COMM, DOT, SLSH,   UP,   RSFT, \
            FN1, LCTL, LALT, LGUI,       SPC,      RGUI,  RALT, LEFT, DOWN, RIGHT),

};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}