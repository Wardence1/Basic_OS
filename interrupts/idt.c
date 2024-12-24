#include "idt.h"
#include <stdbool.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
    u16    isr_low;      // The lower 16 bits of the ISR's address
	u16    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	u8     reserved;     // Set to zero
	u8     attributes;   // Type and attributes; see the IDT page
	u16    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idtEntry;

struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idtr;


void exception_handler(int vector_number, uint32_t error_code) {
    const char* exception_names[] = {
        "Divide Error", "Debug Exception", "Non-Maskable Interrupt",
        "Breakpoint", "Overflow", "Bound Range Exceeded", "Invalid Opcode",
        "Device Not Available", "Double Fault", "Coprocessor Segment Overrun",
        "Invalid TSS", "Segment Not Present", "Stack-Segment Fault",
        "General Protection Fault", "Page Fault", "(Reserved)",
        "x87 Floating-Point Exception", "Alignment Check",
        "Machine Check", "SIMD Floating-Point Exception"
    };

    if (vector_number < 20) {
        printf("Error: \"%s\" (Vector: %d, Error Code: 0x%x)\n",
               exception_names[vector_number], vector_number, error_code);
    } else {
        printf("Exception: Reserved or Unknown (Vector: %d, Error Code: 0x%08X)\n",
               vector_number, error_code);
    }
    asm __volatile__("cli; hlt");
}

__attribute__((aligned(16)))
idtEntry idt[IDT_MAX_DESCRIPTORS];

void idt_set_descriptor(u8 vector, void* isr, u8 flags) {
    idtEntry* descriptor = &idt[vector];

    descriptor->isr_low        = (u32)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (u32)isr >> 16;
    descriptor->reserved       = 0;
}

bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void init_idt() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (u16)sizeof(idtEntry) * IDT_MAX_DESCRIPTORS - 1;

    for (u8 vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    asm __volatile__ ("lidt %0" : : "m"(idtr)); // load the new IDT
    asm __volatile__ ("sti"); // set the interrupt flag
}

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

// Initialize the Programmable Interrupt Controller (PIC)
void remap_pic() {
    // Start initialization of PIC
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // Set vector offsets
    outb(PIC1_DATA, 0x20);  // Master PIC offset
    outb(PIC2_DATA, 0x28);  // Slave PIC offset

    // Configure cascading
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);

    // Set to 8086/88 mode
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // Unmask all interrupts (optional)
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);
}


// Initialize the IDT and PIC
void initIdt() {
    remap_pic();
    init_idt();
}