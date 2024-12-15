#ifndef FILE
#define FILE
#include "../stdio.h"
#include "../string.h"

#define MAX_FILES 10
#define MAX_FILE_NAME_LEN 10

void createFile(char* name, char* content);
void filesInit();
void rmFile(char* name);
void listFiles();

#endif