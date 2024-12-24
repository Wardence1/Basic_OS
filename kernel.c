#include <stdbool.h>
#include <stddef.h>
#include "stdio.h"
#include "io/keyboard.h"
#include "io/io.h"
#include "shell/shell.h"
#include "interrupts/idt.h"
#include "files/file.h"
#include "gdt/gdt.h"

void kernel_main(void) 
{
    initGdt();
    initPICIDT();
    filesInit();
    terminal_initialize();

    printf("Welcome to BasicOS!\nEnter \"help\" for... help\n\n");

    while (true) {
        query();
    }
}
