#include <stdio.h>

#include "simpletron_io.h"
#include "simpletron_cpu.h"
#include "simpletron_memory.h"

int main()
{
	//Memory storage
	int memory[MEMORY_SIZE] = {+0000};

	showWelcomeMessage();

	if (readProgram(memory))
	{
		executeProgram(memory);

		showCpuDump();
		showEmptyLine();	
		showMemoryDump(memory);
	} // end if check program loaded 

	return 0;
} // end main
