/*
    Functions for sending data through ports
*/

#include "io.h"

// Inline implementation of port I/O functions
// These functions provide direct hardware port access

// Read a byte from a specified I/O port
u8 inb(u16 port) {
    u8 ret;
    asm __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// Write a byte to a specified I/O port
void outb(u16 port, u8 data) {
    asm __volatile__ ("outb %0, %1" : : "a"(data), "Nd"(port));
}

// Read a 16-bit word from a port
u16 inw(u16 port) {
    u16 result;
    
    __asm__ volatile (
        "in %%dx, %%ax"  // Read 16-bit word from port
        : "=a" (result)
        : "d" (port)
    );
    
    return result;
}

// Write a 16-bit word to a port
void outw(u16 port, u16 data) {
    __asm__ volatile (
        "out %%ax, %%dx"  // Write 16-bit word to port
        :
        : "a" (data),
          "d" (port)
    );
}