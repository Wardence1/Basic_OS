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

bool cmpStr(const char* str1, const char* str2) {
    // Iterate through both strings until we hit the null terminator
    while (*str1 != '\0' && *str2 != '\0') {
        // Compare each character
        if (*str1 != *str2) {
            return false; // Characters differ, strings are not equal
        }
        str1++;
        str2++;
    }
    // Check if both strings ended (ensures they are the same length)
    return *str1 == '\0' && *str2 == '\0';
}