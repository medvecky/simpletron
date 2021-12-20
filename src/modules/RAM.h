#ifndef _SIMPLETRON_MEMORY_
#define _SIMPLETRON_MEMORY_

#include <stdio.h>

void RAM_write(int *memory, size_t address, int word);
int memoryRead(int *memory, size_t instructionCounter);

#define MEMORY_SIZE 100

#endif
