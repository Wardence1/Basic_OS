#include "idt.h"

typedef struct {
    
} __attribute__((packed)) idt_entry;

void init_idt() {

}

// Initialize the Programmable Interrupt Controller (PIC)
void init_pic() {
    outb(0x20, 0x11); // Initialize master PIC
    outb(0xA0, 0x11); // Initialize slave PIC
    
    outb(0x21, 0x20); // Master PIC vector offset (IRQ0 starts at 0x20)
    outb(0xA1, 0x28); // Slave PIC vector offset (IRQ8 starts at 0x28)

    outb(0x21, 0x04); // Tell master PIC that there is a slave PIC at IRQ2
    outb(0xA1, 0x02); // Tell slave PIC its cascade identity

    outb(0x21, 0x01); // Set master PIC to 8086 mode
    outb(0xA1, 0x01); // Set slave PIC to 8086 mode

    outb(0x21, 0x0);  // Unmask all interrupts on master PIC
    outb(0xA1, 0x0);  // Unmask all interrupts on slave PIC
}

// Initialize the IDT and PIC
void initIdt() {
    init_pic();
    init_idt();
}