#ifndef IO
#define IO

#include "../types.h"

// Read a byte from a specified I/O port
// This function uses inline assembly to directly read from hardware ports
u8 inb(u16 port);

// Write a byte to a specified I/O port
// This function uses inline assembly to directly write to hardware ports
void outb(u16 port, u8 data);

// Read a word (16 bits) from a port
u16 inw(u16 port);

// Write a word (16 bits) to a port
void outw(u16 port, u16 data);

#endif // IO_H
