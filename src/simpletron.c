#include <stdio.h>

#include "modules/simpletron_io.h"
#include "modules/simpletron_cpu.h"
#include "modules/simpletron_memory.h"

int main()
{
	//Memory storage
	int memory[MEMORY_SIZE] = {+0000};

	FILE * outputFile = fopen("simpletron_out.txt", "w");
	if (outputFile == NULL)
	{
		showMessageCantOpenOutputFile();
		return 1;
	}

	showWelcomeMessage(outputFile);
	

	if (readProgram(memory, outputFile))
	{
		executeProgram(memory,outputFile);

		showCpuDump(outputFile);
		showEmptyLine(outputFile);	
		showMemoryDump(memory, outputFile);
	} // end if check program loaded 
	
	fclose(outputFile);

	return 0;
} // end main
