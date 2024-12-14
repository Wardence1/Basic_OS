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

void popChar(char* str, size_t pos) {
    if (str == NULL || str[pos] == '\0') {
        // String is null or empty, nothing to do
        return;
    }
    
    // Shift all characters one position to the left
    int i = pos;
    while (str[i] != '\0') {
        str[i] = str[i + 1];
        i++;
    }
}

void strCopy(char* to, const char* from) {
    for (int i = 0; from[i] != '\0'; i++) {
        to[i] = from[i];
    }
}

// Removes all spaces from the string
// @todo needs malloc
/*
void strCut(char* str) {
    char* temp = malloc(sizeof(char) * strlen(str));
    strCopy(temp, str);
    while (*str) {
        if (*str != ' ') {
            *temp = *str;
            temp++;
        }
        str++;
    }

    strCopy(str, temp);
}
*/