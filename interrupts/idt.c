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


#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#ifdef __x86_64__
typedef unsigned long long int uword_t;
#else
typedef unsigned int uword_t;
#endif

struct interrupt_frame
{
    uword_t ip;
    uword_t cs;
    uword_t flags;
    uword_t sp;
    uword_t ss;
};

void sendEOI(unsigned char irq) {
    if (irq > 7) {
        // Send EOI to the slave PIC
        outb(0xA0, 0x20);
    }
    // Send EOI to the master PIC
    outb(0x20, 0x20);
}

__attribute__((interrupt))
void timer_isr(struct interrupt_frame* frame) {

    sendEOI(0);
}

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

const char scancode_to_ascii[128] = {
    [2] = '1', [3] = '2', [4] = '3', [5] = '4',
    [6] = '5', [7] = '6', [8] = '7', [9] = '8',
    [10] = '9', [11] = '0', [12] = '-', [13] = '=',
    [16] = 'q', [17] = 'w', [18] = 'e', [19] = 'r',
    [20] = 't', [21] = 'y', [22] = 'u', [23] = 'i',
    [24] = 'o', [25] = 'p', [26] = '[', [27] = ']',
    [30] = 'a', [31] = 's', [32] = 'd', [33] = 'f',
    [34] = 'g', [35] = 'h', [36] = 'j',
    [37] = 'k', [38] = 'l', [39] = ';', [40] = '\'',
    [43] = '\\', [44] = 'z',
    [45] = 'x', [46] = 'c', [47] = 'v', [48] = 'b',
    [49] = 'n', [50] = 'm', [51] = ',', [52] = '.',
    [53] = '/', [57] = ' ', [28] = '\n', [15] = '\t',
    [14] = '\b'
};

const char ascii_to_special[128] = {
    ['1'] = '!', ['2'] = '@', ['3'] = '#', ['4'] = '$', ['5'] = '%',
    ['6'] = '^', ['7'] = '&', ['8'] = '*', ['9'] = '(', ['0'] = ')',
    ['-'] = '_', ['='] = '+', ['['] = '{', [']'] = '}', ['\\'] = '|',
    [';'] = ':', ['\''] = '"',
};

bool shift = false;

__attribute__((interrupt))
void keyboard_isr(struct interrupt_frame* frame) {

    unsigned char scancode = inb(KEYBOARD_DATA_PORT);
    unsigned char ascii;

    // Arrow keys
    switch (scancode) {
        // Shift toggling
        case 0x2A: // shift got pressed
            shift = true;
            break;
        case 0xAA: // shift got released
            shift = false;
            break;
        // Arrow keys
        case 72: // up
            //setCursorPosition(getCursorX(), getCursorY()-1);
            break;
        case 75: // left
            if (getCursorX() > 2)
                setCursorPosition(getCursorX()-1, getCursorY());
            break;
        case 77: // right
            if (getCursorX() < VGA_WIDTH - 2)
                setCursorPosition(getCursorX()+1, getCursorY());
            break;
        case 80: // down
            //setCursorPosition(getCursorX(), getCursorY()+1);
            break;
    }

    // If valid convert the scancode to ascii and print
    if ((scancode <= 128) && scancode_to_ascii[scancode]) {
        ascii = scancode_to_ascii[scancode];
        if (shift) {
            // return special characters: !, @, #, ect.
            if (findIn("!@#$%^&*()_+{}|:\"", ascii_to_special[ascii])) {
                putchar(ascii_to_special[ascii]);
            } else {
                // capitilize letters
                putchar(ascii + ('A' - 'a'));
            }
        } else
            putchar(ascii); 
    } 
    
    sendEOI(1);
}


void init_idt() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (u16)sizeof(idtEntry) * IDT_MAX_DESCRIPTORS - 1;

    for (u8 vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    // Set the IRQ interrupts
    idt_set_descriptor(0x20, timer_isr, 0x8E);
    idt_set_descriptor(0x21, keyboard_isr, 0x8E);


    asm __volatile__ ("lidt %0" : : "m"(idtr)); // load the new IDT
    asm __volatile__ ("sti"); // set the interrupt flag
}

void remap_pic() {
    // Save current masks
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);

    // Start initialization in cascade mode
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    // Remap IRQs: IRQ 0-7 to 0x20-0x27, IRQ 8-15 to 0x28-0x2F
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    // Cascade setup
    outb(PIC1_DATA, 0x04); // Tell Master PIC there is a slave at IRQ 2
    outb(PIC2_DATA, 0x02); // Tell Slave PIC its cascade identity

    // Set 8086/88 (MCS-80/85) mode
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    // Restore saved masks
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}


// Initialize the IDT and PIC
void initPICIDT() {
    remap_pic();
    init_idt();
}