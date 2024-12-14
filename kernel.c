#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include "io/keyboard.h"


void kernel_main(void) 
{
    terminal_initialize();

    int scanCode;
    while (true) {
        scanCode = read_key();
        if (scanCode != 0)
            putchar(scanCode);
    }
}