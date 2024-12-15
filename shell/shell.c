/*
    This is what allows input into the kernel
*/

#include "shell.h"

// Asks for input
void query() {
    printf("> ");
    size_t queryPos = getCursorY();
    int endBuffer = 0; // The end of the command being entered
    setCursorPosition(2, queryPos);

    char character = 0;
    char inputBuffer[VGA_WIDTH];
    while (character != '\n') {
        character = read_key();
        if (character != 0) {
            putchar(character);
            // make sure the cursor doesn't go out off the line
            if (getCursorX() < 2) {
                setCursorPosition(2, queryPos);
            } else if(getCursorX() > VGA_WIDTH - 1) {
                setCursorPosition(VGA_WIDTH-1, queryPos);
            }

            inputBuffer[getCursorX()-2] = character;
            if (getCursorX()-2 > endBuffer) {
                endBuffer = getCursorX()-2;
            } 
        }
    }

    popChar(inputBuffer, 0); // Get rid of the \n at the beginning
    inputBuffer[endBuffer] = '\0'; // Add null operatior to input buffer

    // https://www.youtube.com/watch?v=BXLAqEchBW0
    if (getCursorY() != VGA_HEIGHT-1) {
        putchar('\n');
    } else {
        setCursorPosition(0, getCursorY());
    }

    command(inputBuffer);
}

// Takes command and calls a syscall
void command(const char* cmd) {
    if (cmpStr(cmd, "clear")) {
        clearTerminal();
        setCursorPosition(0, 0);
    } else if (cmpStr(cmd, "help")) {
        printf("\"clear\" - clears the terminal\n");
    }
}