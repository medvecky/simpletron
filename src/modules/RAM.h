#ifndef _RAM_
#define _RAM_

#include <stdio.h>

void RAM_write(int *memory, size_t address, int word);
int RAM_read(int *memory, size_t instructionCounter);

#define MEMORY_SIZE 100

#endif
