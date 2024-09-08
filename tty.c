#include "tty.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;


static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
    return (uint16_t) uc | (uint16_t) color << 8;
}


void terminal_initialize(void) 
{
    terminal_row = 0;
    terminal_column = 0;
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
    // Characters
    default:
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
    }

    // wrap text
    if (terminal_column >= VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;
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

void terminal_write(const char* data, size_t size) 
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}