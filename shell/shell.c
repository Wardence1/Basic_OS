/*
    This is what allows input into the kernel
*/

#include "shell.h"

// Asks for input
void query() {
    printf("> ");
    size_t queryPos = getCursorY();
    setCursorPosition(3, queryPos);

    char character = 0;
    char inputBuffer[VGA_WIDTH];
    while (character != '\n') {
        character = read_key();
        if (character != 0) {
            putchar(character);
            if (getCursorX() < 3) {
                setCursorPosition(3, queryPos);
            } else if(getCursorX() > VGA_WIDTH - 1) {
                setCursorPosition(VGA_WIDTH-1, queryPos);
            }

            inputBuffer[getCursorX()-3] = character;
        }
    }
    putchar('\n');
    command(inputBuffer);
}

// Takes command and calls a syscall
void command(const char* cmd) {
    if (cmpStr(cmd, "clear")) {
        clearTerminal();
        setCursorPosition(0, 0);
    }
}