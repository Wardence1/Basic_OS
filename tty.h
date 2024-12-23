#ifndef TTY
#define TTY

#include <stddef.h>
#include "types.h"


/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static const s8 VGA_WIDTH = 80;
static const s8 VGA_HEIGHT = 25;

void terminal_initialize(void);
void terminal_setcolor(u8 color);
void wrapScroll();
void terminal_putentryat(char c, u8 color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void clearTerminal();
char getChar(int x, int y);
void setCursorPosition(s8 x, s8 y);
s8 getCursorX();
s8 getCursorY();

#endif