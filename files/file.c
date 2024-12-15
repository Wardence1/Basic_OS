/*
    All files can only hold 50 characters for now.
*/

// C strings are annoying to work with, memory errors are really easy to come by.

#include "file.h"

typedef struct {
    char name[MAX_FILE_NAME_LEN];
    char content[50];
} file;

file files[MAX_FILES - 1];

void filesInit() {
    for (int i = 0; i < 9; i++) {
        files[i].name[0] = '\0';
    } 
}

void createFile(char* name, char* content) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].name[0] == '\0') {
            strCopy(files[i].name, name);
            strCopy(files[i].content, content);
            return;
        }
    }
    printf("Max files stored.\n");
}

void rmFile(char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (cmpStr(files[i].name, name)) {
            files[i].name[0] = '\0';
            files[i].content[0] = '\0';
            return;
        }
    } 
    printf("File name ");
    printf(name);
    printf(" could not be found\n");
}

void listFiles() {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].name[0] != '\0') {
            printf(files[i].name);
            printf(" - ");
            printf(files[i].content);
            putchar('\n');
        }
    }
}