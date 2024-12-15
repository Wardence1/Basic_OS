/*
    Standart input output
*/

#include "stdio.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "string.h"

void putchar(const char c) {

	terminal_putchar(c);
}

void printf(const char* fmt, ...) {

	va_list ap;

	int ival; // integer value
	//double fval; // double value

	char buffer[15]; // This is for storing integers/floats and printing them.

	va_start(ap, fmt);

	for (size_t i=0; i<strlen(fmt); i++) {

		if (fmt[i] != '%') {
			terminal_putchar(fmt[i]);
			continue;
		}

		// Goes through all the % printables
		if (fmt[i+1]) {
			switch(fmt[++i]) {

				// Percent
			case '%':
				terminal_putchar('%');
				break;
				
				// Integer
			case 'd':
				ival = va_arg(ap, int);
				int i = 0;

				if (ival == 0) {
					terminal_putchar('0');
					break;
				}

				if (ival < 0) {
					terminal_putchar('-');
					ival = -ival;
				}

				while (ival > 0) {
					buffer[i++] = '0' + (ival % 10); // Puts the number in the buffer in desending order.
					ival /= 10;
				}

				while (i > 0) {
					terminal_putchar(buffer[--i]);
				}

				break;
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