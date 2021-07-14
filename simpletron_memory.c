#include <stdio.h>

#include "simpletron_memory.h"
 
void memoryWrite(int *memory, size_t address, int word)
{
	memory[address] = word;
} // end function memoryWrite

int  memoryRead(int *memory, size_t instructionCounter)
{
	return memory[instructionCounter];
} // end function memoryRead
