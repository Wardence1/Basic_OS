#include <stddef.h>
#include <stdint.h>

#ifndef MEMORY
#define MEMORY

void* malloc(unsigned int bytes);
void free(void* ap);
int memcmp(const void* aptr, const void* bptr, size_t size);
void* memset(void* bufptr, int value, size_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);

#endif