/*
    Standart input output
*/

#include "stdio.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include "string.h"

void putchar(const char c) {

	terminal_putchar(c);
}

void printf(const char* fmt, ...) {

    va_list ap;

    int ival; // integer value
    double fval; // floating point value
    char buffer[65];
    
    va_start(ap, fmt);

    for (size_t i = 0; i < strlen(fmt); i++) {

        if (fmt[i] != '%') {
            terminal_putchar(fmt[i]);
            continue;
        }

        // Goes through all the % printables
        if (fmt[i + 1]) {
            switch (fmt[++i]) {

                // Percent
            case '%':
                terminal_putchar('%');
                break;

                // Integer
            case 'd': {
                ival = va_arg(ap, int);
                int j = 0;

                if (ival == 0) {
                    terminal_putchar('0');
                    break;
                }

                if (ival < 0) {
                    terminal_putchar('-');
                    ival = -ival;
                }

                while (ival > 0) {
                    buffer[j++] = '0' + (ival % 10); // Puts the number in the buffer in descending order.
                    ival /= 10;
                }

                while (j > 0) {
                    terminal_putchar(buffer[--j]);
                }

                break;
            }

                // Hexadecimal for unsigned int
            case 'x': {
                unsigned int hval = va_arg(ap, unsigned int);
                int j = 0;

                if (hval == 0) {
                    terminal_putchar('0');
                    break;
                }

                while (hval > 0) {
                    unsigned int digit = hval % 16;
                    buffer[j++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                    hval /= 16;
                }

                while (j > 0) {
                    terminal_putchar(buffer[--j]);
                }

                break;
            }

                // Hexadecimal for unsigned long long
            case 'l': {
                if (fmt[i + 1] == 'l' && fmt[i + 2] == 'x') {
                    i += 2; // Skip "llx"
                    unsigned long long hval = va_arg(ap, unsigned long long);
                    int j = 0;

                    if (hval == 0) {
                        terminal_putchar('0');
                        break;
                    }

                    while (hval > 0) {
                        unsigned long long digit = hval % 16;
                        buffer[j++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
                        hval /= 16;
                    }

                    while (j > 0) {
                        terminal_putchar(buffer[--j]);
                    }
                } else {
                    terminal_write("\nError: Unsupported format specifier starting with 'l'!\n", 55);
                }

                break;
            }

                // Floating point
            case 'f': {
                fval = va_arg(ap, double);
                if (fval < 0) {
                    terminal_putchar('-');
                    fval = -fval;
                }

                // Integer part
                int int_part = (int)fval;
                double frac_part = fval - int_part;

                // Print integer part
                int j = 0;
                if (int_part == 0) {
                    terminal_putchar('0');
                } else {
                    while (int_part > 0) {
                        buffer[j++] = '0' + (int_part % 10);
                        int_part /= 10;
                    }
                    while (j > 0) {
                        terminal_putchar(buffer[--j]);
                    }
                }

                terminal_putchar('.');

                // Print fractional part (up to 6 decimal places)
                for (int k = 0; k < 6; k++) {
                    frac_part *= 10;
                    int digit = (int)frac_part;
                    terminal_putchar('0' + digit);
                    frac_part -= digit;
                }

                break;
            }

            default:
                terminal_write("\nError: Unrecognized format specifier!!! ):<\n", 48);
            }
        } else {
            terminal_write("\nError: put something after the '%' for it to actually work!!! ):<\n", 66);
        }
    }

    va_end(ap);
}

void println(const char* str) {
	printf(str);
	putchar('\n');
}