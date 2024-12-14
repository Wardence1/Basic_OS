#ifndef STRING
#define STRING

#include <stddef.h>
#include <stdbool.h>

size_t strlen(const char* str);
char findIn(const char* str, char search);
bool cmpStr(const char* str1, const char* str2);

#endif