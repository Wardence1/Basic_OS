#include <stddef.h>
#include <stdint.h>

#ifndef MEMORY
#define MEMORY

void* malloc(unsigned int bytes);
void free(void* ap);

#endif