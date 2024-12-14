#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include "io/keyboard.h"
#include "shell/shell.h"

void kernel_main(void) 
{
    terminal_initialize();

    printf("Welcom to BasicOS!\nIt's very basic...\n\n");

    while (true) {
        query();
    }
}