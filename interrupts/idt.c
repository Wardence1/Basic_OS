/* 
    @todo get this to work, I just got this from online, don't know what I'm doing.
    I'm currently more interested in memory.
    I'll come back to this when I feel like reaidng on IDTs.
*/

#include "idt.h"

#define NUM_INTERRUPTS 256

// Structure to hold IDT entries
struct IDTEntry {
    uint16_t offset_low;   // Lower 16 bits of the handler function address
    uint16_t selector;     // Kernel segment selector
    uint8_t zero;          // Reserved (set to 0)
    uint8_t flags;         // Flags (interrupt gate type, privilege level, etc.)
    uint16_t offset_high;  // Upper 16 bits of the handler function address
} __attribute__((packed));

// IDT pointer structure
struct IDTPointer {
    uint16_t limit;   // Size of the IDT (number of entries * size of entry)
    uint32_t base;    // Base address of the IDT
} __attribute__((packed));

// Declare IDT and its pointer
static struct IDTEntry idt[NUM_INTERRUPTS];
static struct IDTPointer idt_pointer;


// Assembly function to load the IDT
extern void loadIdt(struct IDTPointer *idt_ptr);

// Declare handler functions
extern void isr_stub(void); // Generic ISR stub
extern void keyboard_handler_stub(void); // Keyboard interrupt stub

void key_test(void) {
    uint8_t scancode = inb(0x60); // Read the scancode from the keyboard data port

    // Process the scancode (convert to character or handle key press)
    printf("%d", scancode);
    //while(1);
    // printf("Scancode: %x\n", scancode);

    // Send End of Interrupt (EOI) signal to PIC
    outb(0x20, 0x20); // Notify master PIC
}

void isr_handler(uint32_t interrupt_number) {
    // Debug: Print the interrupt number (for kernel logging or debugging)
    printf("Interrupt received: %u\n", interrupt_number);

    // Handle specific interrupts
    switch (interrupt_number) {
        case 0:
            // Example: Divide by zero error
            printf("Exception: Divide by Zero\n");
            break;

        case 33:
            // IRQ1: Keyboard interrupt
            key_test();
            break;

        default:
            // Unhandled interrupt
            printf("Unhandled interrupt: %u\n", interrupt_number);
            break;
    }

    // Send End of Interrupt (EOI) signal if it's a hardware interrupt
    if (interrupt_number >= 32 && interrupt_number <= 47) {
        outb(0x20, 0x20); // Notify master PIC
        if (interrupt_number >= 40) {
            outb(0xA0, 0x20); // Notify slave PIC if needed
        }
    }
}
// Helper function to set an IDT entry
void set_idt_entry(int interrupt_number, void (*handler)(void), uint8_t flags) {
    uint32_t handler_address = (uint32_t)handler;

    idt[interrupt_number].offset_low = handler_address & 0xFFFF;
    idt[interrupt_number].offset_high = (handler_address >> 16) & 0xFFFF;
    idt[interrupt_number].selector = 0x08; // Kernel code segment (typically 0x08)
    idt[interrupt_number].zero = 0;
    idt[interrupt_number].flags = flags;
}

// Initialize the IDT
void init_idt() {
    for (int i = 0; i < NUM_INTERRUPTS; i++) {
        set_idt_entry(i, isr_stub, 0x8E); // 0x8E: Present, ring 0, interrupt gate
    }

    // Set keyboard interrupt handler (IRQ1 mapped to interrupt 33)
    set_idt_entry(33, keyboard_handler_stub, 0x8E);

    // Load the IDT
    idt_pointer.limit = sizeof(idt) - 1;
    idt_pointer.base = (uint32_t)&idt;
    loadIdt(&idt_pointer);
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
void idt_init() {
    init_pic(); // Initialize PIC first
    init_idt(); // Then initialize the IDT
}