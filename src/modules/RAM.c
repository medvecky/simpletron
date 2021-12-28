#include <stdbool.h>
#include <stdio.h>

#include "RAM.h"
 
bool RAM_write(int *memory, size_t address, int word)
{
    if (address < 0 || address >= MEMORY_SIZE)
    {
        return false;
    } // end if check address boundary
    
    memory[address] = word;
    
    return true;
} // end function RAM_write

int   RAM_read(int *memory, size_t address)
{
    return memory[address];
} // end function memoryRead
