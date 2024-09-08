#ifndef STDIO
#define STDIO
#include <stdint.h>
#include "tty.h"

void printf(const char* fmt, ...);
void putchar(const char c);

#endif