#ifndef KEYBOARD
#define KEYBOARD

#include "../types.h"
#include <stdbool.h>
#include "../stdio.h"
#include "io.h"
#include "../string.h"

u8 read_key();
void clearKeyboardBuffer();

#endif