/*
    Terminal config
*/

#include "tty.h"
#include "stdbool.h"
#include "io/io.h"
#include "stdio.h"

#define VGA_CMD_PORT  0x3D4
#define VGA_DATA_PORT 0x3D5

s8 terminal_row;
s8 terminal_column;
u8 terminal_color;
u16* terminal_buffer;
bool backspace = false; // Is true if backspace is pressed


static inline u16 vga_entry(unsigned char uc, u8 color) 
{
    return (u16) uc | (u16) color << 8;
}

void move_cursor(u8 x, u8 y) {
    u16 position = y * VGA_WIDTH + x;

    // Send the high byte of the cursor position
    outb(VGA_CMD_PORT, 0x0E);       // Select high byte register
    outb(VGA_DATA_PORT, (position >> 8) & 0xFF);

    // Send the low byte of the cursor position
    outb(VGA_CMD_PORT, 0x0F);       // Select low byte register
    outb(VGA_DATA_PORT, position & 0xFF);
}

void terminal_initialize(void) 
{
    terminal_row = 0;
    terminal_column = 0;
    move_cursor(terminal_row, terminal_column);
    terminal_color = VGA_COLOR_LIGHT_GREY;
    terminal_buffer = (u16*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}


void terminal_setcolor(u8 color) 
{
    terminal_color = color;
}

void terminal_putentryat(char c, u8 color, size_t x, size_t y) 
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
    switch (c) {
    // Escape sequences
    case '\n':
        terminal_row++;
        terminal_column = 0;
        break;
    case '\r':
        terminal_column = 0;
        break;
    case '\t':
        terminal_column += 4;
        break;
    case '\b':
        terminal_column--;
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        break;
    // Characters
    default:
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
    }

    wrapScroll();

    move_cursor(terminal_column, terminal_row);
}

void terminal_write(const char* data, size_t size) 
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

// Gets the character at a selected position on the screen
char getChar(int x, int y) {
    return terminal_buffer[y * VGA_WIDTH + x];
}

// Wraps and scrolls the terminal
void wrapScroll() {
    // wrap text
    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
    } else if (terminal_column < 0) {
        terminal_column = 0;
        if (terminal_row > 0) {
            terminal_row--;
            terminal_column = VGA_WIDTH-1;
        }
    }

    // stop the cursor from going up too high
    if (terminal_row < 0) {
        terminal_row = 0;
    }

    // scroll the terminal
    if (terminal_row >= VGA_HEIGHT) {

        // move lines up by one
        for (size_t y=1; y<VGA_HEIGHT; y++) {
            for (size_t x=0; x<VGA_WIDTH; x++) {
                terminal_putentryat(getChar(x, y), terminal_color, x, y-1);
            }
        }

        // clear the last row
        for (size_t x=0; x<VGA_WIDTH; x++) {
            terminal_putentryat(' ', terminal_color, x, VGA_HEIGHT-1);
        }

        terminal_row = VGA_HEIGHT-1;
    }
}

void clearTerminal() {
    
    for (int i = 0; i < VGA_HEIGHT; i++) {
        for (int j = 0; j < VGA_WIDTH-1; j++) {
            terminal_putentryat(' ', terminal_color, j, i);
        }
    }
}

void setCursorPosition(s8 x, s8 y) {
    terminal_column = x;
    terminal_row = y;
    wrapScroll();
    move_cursor(terminal_column, terminal_row);
}

s8 getCursorX() {
    return terminal_column;
}

s8 getCursorY() {
    return terminal_row;
}
