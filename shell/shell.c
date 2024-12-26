/*
    This is what allows input into the kernel
*/

#include "shell.h"

// Asks for input
// @todo fix the terminal scrolling input issue
// @todo Fix the quotes on title reading issue
/*
void query() {
    printf("> ");
    size_t queryPos = getCursorY();
    int endBuffer = 0; // The end of the command being entered
    setCursorPosition(2, queryPos);

    char character = 0;
    char inputBuffer[VGA_WIDTH+5]; // the +5 is for memory safety
    while (character != '\n') {
        character = read_key();
        if (character != 0) {
            putchar(character);
            // make sure the cursor doesn't go out off the line
            if (getCursorX() < 2) {
                setCursorPosition(2, queryPos);
            } else if(getCursorX() > VGA_WIDTH - 2) {
                setCursorPosition(VGA_WIDTH-2, queryPos);
            }

            inputBuffer[getCursorX()-2] = character;
            if (getCursorX()-2 > endBuffer) {
                endBuffer = getCursorX()-2;
            } 
        }
    }

    int xPos;
    for (xPos = 1; xPos < VGA_WIDTH-1; xPos++) {
        inputBuffer[xPos] = getChar(xPos, queryPos);
    }

    popChar(inputBuffer, 0); // Get rid of the \n at the beginning
    inputBuffer[xPos+1] = '\0';


    // https://www.youtube.com/watch?v=BXLAqEchBW0
    if (getCursorY() != VGA_HEIGHT-1) {
        putchar('\n');
    } else {
        setCursorPosition(0, getCursorY());
    }

    strCut(inputBuffer);
    command(inputBuffer);
}

// Takes command and calls a syscall
void command(const char* cmd) {

    char fWord[50]; // first word, hehe
    char sWord[50]; // second word
    char tWord[50]; // second word

    getWord(cmd, 0, fWord); // get the first word
    getWord(cmd, 1, sWord); // get the second word
    getWord(cmd, 2, tWord); // get the third word

    if (cmpStr(cmd, "clear")) {
        clearTerminal();
        setCursorPosition(0, 0);

    } else if (cmpStr(cmd, "ls")) {
        listFiles();

    } else if (cmpStr(fWord, "touch")) {
        if (strlen(sWord) > MAX_FILE_NAME_LEN) printf("The title can be at most %d characters long.\n", MAX_FILE_NAME_LEN);
        truncateString(sWord, MAX_FILE_NAME_LEN);
        createFile(sWord, tWord);

    } else if (cmpStr(fWord, "rm")) {
        rmFile(sWord);

    } else if (cmpStr(cmd, "help")) {
        printf("\"clear\" - clears the terminal\n");
        printf("\"ls\" - lists all files\n");
        printf("\"touch\" + file name + file contents - touch creates a file\n");
        printf("\"rm\" + file name - removes the specified file\n");
    }
}*/