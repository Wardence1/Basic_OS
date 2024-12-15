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

// Removes spaces at the beginning and end of the string
void strCut(char* str) {
    int start = 0, end, i;

    // Find the first non-space character
    while (str[start] == ' ' && str[start] != '\0') {
        start++;
    }

    // Find the last non-space character
    end = strlen(str) - 1;
    while (end >= start && str[end] == ' ') {
        end--;
    }

    // Shift characters to the beginning of the string
    for (i = 0; start <= end; start++, i++) {
        str[i] = str[start];
    }

    // Null-terminate the trimmed string
    str[i] = '\0';
}

void getWord(const char* str, int position, char* word) {
    int i = 0, j = 0, wordCount = 0;

    // Iterate through the string
    while (str[i] != '\0') {
        // Skip any spaces between words
        while (str[i] == ' ') {
            i++;
        }

        // If we've reached the desired word
        if (wordCount == position) {
            // Copy characters of the word to 'word' array
            while (str[i] != ' ' && str[i] != '\0') {
                word[j++] = str[i++];
            }
            word[j] = '\0';  // Null-terminate the word
            return;
        }

        // Skip the current word
        while (str[i] != ' ' && str[i] != '\0') {
            i++;
        }

        wordCount++;  // Move to the next word
    }

    // If the position is out of bounds (word doesn't exist), return an empty string
    word[0] = '\0';
}


void substring(char *source, int start, int length) {
    int i, sourceLength = strlen(source);

    // Ensure the start is within bounds
    if (start < 0 || start >= sourceLength) {
        source[0] = '\0'; // If start is invalid, clear the string
        return;
    }

    // Shift characters from the start position by the desired length
    for (i = 0; i < length && source[start + i] != '\0'; i++) {
        source[i] = source[start + i];
    }

    source[i] = '\0'; // Null-terminate the modified source string
}