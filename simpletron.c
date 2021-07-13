#include <stdio.h>

#include "simpletron_io.h"

int main()
{
	//Memory storage
	int memory[100] = {+0000};
	
	puts("Memory before reading:");

	showMemoryDump(memory);

	showWelcomeMessage();
	readProgramFromConsole(memory);

	puts("Memory after reading:");

	showMemoryDump(memory);	
	return 0;
} // end main
