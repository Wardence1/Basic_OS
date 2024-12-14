/*
    Terminal config
*/

#include "tty.h"
#include "stdbool.h"
#include "io/io.h"
#include "stdio.h"

#define VGA_CMD_PORT  0x3D4
#define VGA_DATA_PORT 0x3D5

int8_t terminal_row;
int8_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
bool backspace = false; // Is true if backspace is pressed


static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

void move_cursor(uint8_t x, uint8_t y) {
    uint16_t position = y * VGA_WIDTH + x;

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
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}


void terminal_setcolor(uint8_t color) 
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
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

    // scroll the screen
    if (terminal_row >= VGA_HEIGHT) {

        for (size_t y=1; y<VGA_HEIGHT; y++) {
            for (size_t x=0; x<VGA_WIDTH; x++)
                terminal_buffer[(y-1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
        }

        // clear the last row
        for (size_t x=0; x<VGA_WIDTH; x++) {
            terminal_buffer[(VGA_HEIGHT-1) * VGA_WIDTH + x] = 0;
        }

        terminal_row--;
    }
}

void clearTerminal() {
    
    for (int i = 0; i < VGA_HEIGHT; i++) {
        for (int j = 0; j < VGA_WIDTH-1; j++) {
            terminal_buffer[i * VGA_WIDTH + j] = 0;
        }
    }
}

void setCursorPosition(int8_t x, int8_t y) {
    terminal_column = x;
    terminal_row = y;
    wrapScroll();
    move_cursor(terminal_column, terminal_row);
}

int8_t getCursorX() {
    return terminal_column;
}

int8_t getCursorY() {
    return terminal_row;
}
