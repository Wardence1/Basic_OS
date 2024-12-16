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

void strCopy(char *to, const char *from) {
    int i = 0;

    // Copy each character from the source to the destination
    while (from[i] != '\0') {
        to[i] = from[i];
        i++;
    }

    // Null-terminate the destination string
    to[i] = '\0';
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

// Text surrouned by quotes counts as a word
void getWord(const char* str, int position, char* word) {
    int i = 0, j = 0, wordCount = 0;
    bool inQuotes = false;  // Flag to track if we are inside quotes

    // Iterate through the string
    while (str[i] != '\0') {
        // Skip spaces if not inside quotes
        while (str[i] == ' ' && !inQuotes) {
            i++;
        }

        // If we've reached a non-space character
        if (str[i] != '\0') {
            // Handle quoted text
            if (str[i] == '"') {
                inQuotes = !inQuotes;  // Toggle inQuotes flag
                i++;  // Move past the quote
                if (!inQuotes) {
                    // Closing quote reached
                    word[j] = '\0';  // Null-terminate the word
                    return;
                }
            }

            // Check if this is the desired word
            if (wordCount == position) {
                while ((inQuotes || (str[i] != ' ' && str[i] != '\0')) && str[i] != '"') {
                    word[j++] = str[i++];
                }

                // If we exit quotes, advance the pointer
                if (str[i] == '"') {
                    i++;
                }

                word[j] = '\0';  // Null-terminate the word
                return;
            }

            // Skip the current word or quoted text
            while ((inQuotes || (str[i] != ' ' && str[i] != '\0')) && str[i] != '"') {
                i++;
            }

            // If we exit quotes, advance the pointer
            if (str[i] == '"') {
                i++;
            }

            // Increment word count if we're exiting a word
            if (!inQuotes) {
                wordCount++;
            }
        }
    }

    // If the word at the position doesn't exist, return an empty string
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


void truncateString(char *str, int maxLength) {
    // Check if the string is longer than the desired length
    if (strlen(str) > (size_t)maxLength) {
        str[maxLength] = '\0'; // Null-terminate the string at the specified length
    }
}