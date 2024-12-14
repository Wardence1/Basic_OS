/*
    Functions for string use
*/

#include "string.h"
#include "stdio.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

char findIn(const char* str, char search) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == search) {
            return str[i];
        }
    }
    return 0;
}