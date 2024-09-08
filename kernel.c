#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif




void kernel_main(void) 
{

    /* Initialize terminal interface */
    terminal_initialize();

    unsigned int num = 655369966;


    terminal_setcolor(VGA_COLOR_RED);

    printf("   HHHHHHHHHHHH    \n");
    printf("HHHHHHHHHHHHHHHHHHH    \n");
    printf("HHHHHHHHHHHHHHHHHHH    \n");
    printf("HHHHHHHHHHHHHHHHHHH    \n");
    printf("HHHHHHHHHHHHHHHHHHH    \n");
    printf("HHHHHHHHHHHHHHHHHHH    \n");
    printf("HHHHHHHHHHHHHHHHHHH    \n");
    printf("   HHHHHHHHHHHH    \n");

    terminal_setcolor(VGA_COLOR_LIGHT_GREY);


    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("I'm at the bottom! YAY!\nOh, that thing up there's getting cut in half... oh well.");

    printf("\nHere are %% some \\ numbers: %d, %d. That's all.", num, 65);
}
