/*
    Functions for keyboard input
*/

#include "keyboard.h"
#include "../interrupts/idt.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

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

bool shift = false;

__attribute__((interrupt))
void keyboard_isr(struct interrupt_frame* frame) {

    unsigned char scancode = inb(KEYBOARD_DATA_PORT);
    unsigned char ascii;

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
            if (getCursorX() > 2)
                setCursorPosition(getCursorX()-1, getCursorY());
            break;
        case 77: // right
            if (getCursorX() < VGA_WIDTH - 2)
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
            if (findIn("!@#$%^&*()_+{}|:\"", ascii_to_special[ascii])) {
                putchar(ascii_to_special[ascii]);
            } else {
                // capitilize letters
                putchar(ascii + ('A' - 'a'));
            }
        } else
            putchar(ascii); 
    } 
    
    sendEOI(1);
}
