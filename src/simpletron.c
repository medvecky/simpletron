#include <stdio.h>
#include <stdlib.h>

#include "modules/IO.h"
#include "modules/CPU.h"
#include "modules/RAM.h"

#define OUTPUT_FILE "simpletron_out.txt"

int main()
{
	//Memory storage
	int memory[MEMORY_SIZE] = {+0000};

	FILE * outputFile = fopen(OUTPUT_FILE, "w");
	if (outputFile == NULL)
	{
		IO_showMessageCantOpenOutputFile();
		return EXIT_FAILURE;
	} // end if check ouput gfile exists

	IO_showWelcomeMessage(outputFile);
	

	if (IO_readProgram(memory, outputFile))
	{
		CPU_executeProgram(memory,outputFile);

		IO_showCpuDump(outputFile);
		IO_showEmptyLine(outputFile);	
		IO_showMemoryDump(memory, outputFile);
	} // end if check program loaded 
	
	fclose(outputFile);

	return EXIT_SUCCESS;
} // end main
