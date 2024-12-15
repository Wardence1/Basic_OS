#ifndef STRING
#define STRING

#include <stddef.h>
#include <stdbool.h>

size_t strlen(const char* str);
char findIn(const char* str, char search);
bool cmpStr(const char* str1, const char* str2);
void popChar(char* str, size_t pos);
void strCopy(char* to, const char* from);
void strCut(char* str);
void getWord(const char* str, int position, char* word);
void substring(char *source, int start, int length);

#endif