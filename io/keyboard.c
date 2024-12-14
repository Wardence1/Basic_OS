/*
    Functions for keyboard input
*/

#include <stdint.h>
#include <stdbool.h>
#include "../stdio.h"
#include "keyboard.h"
#include "io.h"
#include "../string.h"


#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

bool shift = false; // Is true if shift is held in

const char scancode_to_ascii[128] = {
    [2] = '1', [3] = '2', [4] = '3', [5] = '4',
    [6] = '5', [7] = '6', [8] = '7', [9] = '8',
    [10] = '9', [11] = '0', [12] = '-', [13] = '=',
    [16] = 'q', [17] = 'w', [18] = 'e', [19] = 'r',
    [20] = 't', [21] = 'y', [22] = 'u', [23] = 'i',
    [24] = 'o', [25] = 'p', [26] = '[', [27] = ']',
    [30] = 'a', [31] = 's', [32] = 'd', [33] = 'f',
    [34] = 'g', [35] = 'h', [36] = 'j',
    [37] = 'k', [38] = 'l', [39] = ';', [40] = '\'',
    [43] = '\\', [44] = 'z',
    [45] = 'x', [46] = 'c', [47] = 'v', [48] = 'b',
    [49] = 'n', [50] = 'm', [51] = ',', [52] = '.',
    [53] = '/', [57] = ' ', [28] = '\n', [15] = '\t',
    [14] = '\b'
};

const char ascii_to_special[128] = {
    ['1'] = '!', ['2'] = '@', ['3'] = '#', ['4'] = '$', ['5'] = '%',
    ['6'] = '^', ['7'] = '&', ['8'] = '*', ['9'] = '(', ['0'] = ')',
    ['-'] = '_', ['='] = '+', ['['] = '{', [']'] = '}', ['\\'] = '|',
    [';'] = ':', ['\''] = '"',
};

uint8_t read_key() {
    unsigned char scancode;
    unsigned char ascii;

    // Only move through when a key is pressed
    while ((inb(KEYBOARD_STATUS_PORT) & 0x01) == 0) ;

    scancode = inb(KEYBOARD_DATA_PORT);

    // Arrow keys
    switch (scancode) {
        // Shift toggling
        case 0x2A: // shift got pressed
            shift = true;
            break;
        case 0xAA: // shift got released
            shift = false;
            break;
        // Arrow keys
        case 72: // up
            //setCursorPosition(getCursorX(), getCursorY()-1);
            break;
        case 75: // left
            setCursorPosition(getCursorX()-1, getCursorY());
            break;
        case 77: // right
            setCursorPosition(getCursorX()+1, getCursorY());
            break;
        case 80: // down
            //setCursorPosition(getCursorX(), getCursorY()+1);
            break;
    }

    // If valid convert the scancode to ascii and print
    if ((scancode <= 128) && scancode_to_ascii[scancode]) {
        ascii = scancode_to_ascii[scancode];
        if (shift) {
            // return special characters: !, @, #, ect.
            if (findIn("!@#$%^&*()_+{}|:\"", ascii_to_special[ascii]))
                return ascii_to_special[ascii];
            // capitilize letters
            return ascii + ('A' - 'a'); 
        } else
            return ascii;
    } else {
        return 0;
    }    
}