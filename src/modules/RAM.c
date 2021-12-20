#include <stdio.h>

#include "RAM.h"
 
void RAM_write(int *memory, size_t address, int word)
{
	memory[address] = word;
} // end function RAM_write

int   RAM_read(int *memory, size_t instructionCounter)
{
	return memory[instructionCounter];
} // end function memoryRead
