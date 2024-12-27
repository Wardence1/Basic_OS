#ifndef IDT
#define IDT

#include "../types.h"
#include "../io/io.h"
#include "../stdio.h"
#include "../io/keyboard.h"

void initPICIDT();

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

void sendEOI(unsigned char irq);

__attribute__((interrupt))
void timer_isr(struct interrupt_frame* frame);
__attribute__((interrupt))
void keyboard_isr(struct interrupt_frame* frame);

#endif