#ifndef IO
#define IO

#include <stdint.h>

// Read a byte from a specified I/O port
// This function uses inline assembly to directly read from hardware ports
uint8_t inb(uint16_t port);

// Write a byte to a specified I/O port
// This function uses inline assembly to directly write to hardware ports
void outb(uint16_t port, uint8_t data);

// Read a word (16 bits) from a port
uint16_t inw(uint16_t port);

// Write a word (16 bits) to a port
void outw(uint16_t port, uint16_t data);

#endif // IO_H
