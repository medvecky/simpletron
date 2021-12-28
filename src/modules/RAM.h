#ifndef _RAM_
#define _RAM_

#include <stdbool.h>
#include <stdio.h>

bool RAM_write(int *memory, size_t address, int word);
int RAM_read(int *memory, size_t address);

#define MEMORY_SIZE 100
#define ERROR_VALUE 55555

#endif
