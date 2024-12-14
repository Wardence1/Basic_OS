#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include "io/keyboard.h"
#include "shell/shell.h"

void kernel_main(void) 
{
    terminal_initialize();

    while (true) {
        query();
    }
}