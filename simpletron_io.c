#include <stdio.h>
#include <stdlib.h>

#include "simpletron_io.h"
#include "simpletron_memory.h"

#define RAM_SIZE 100

static int getDataWord();
static char * getDataString();

void showWelcomeMessage()
{
	puts("*** Welcome to Simpletron! ***");
	puts("*** Please enter your program one instruction ***");
	puts("*** (or data word) at a time. I will type the ***");
	puts("*** location number and question mark (?).    ***");
	puts("*** You then type word for that location.     ***");
	puts("*** Type the sentinel -99999 to stop entering ***");
	puts("*** your program.  ***");
} // end function showWelcomeMessage

void  readProgramFromConsole(int *memory)
{
	size_t wordCounter = 0;
	int dataWord;
	
	printf("%02zu ? ", wordCounter);
	while((dataWord = getDataWord()) != -99999 && wordCounter < RAM_SIZE)
	{
		memoryWrite(memory, wordCounter++, dataWord);
		printf("%02zu ? ", wordCounter);
	} // end while readData loop
} // end function readProgramfromConsole

static int getDataWord()
{
	int dataWord;
	int scanfResult;
	while((scanfResult = scanf("%d", &dataWord)) != 1)
	{
		while (getchar() != '\n');
		puts("Invalid data format.");
		puts("Please enter correct data word");
	} // end while read data end validation
	while (getchar() != '\n');
	return dataWord;
} // end function getDataWord

void showMemoryDump(int *memory)
{
	puts("MEMORY:");
	
	printf("%c\t", ' ' );
	for (size_t index = 0; index < 10; index++)
	{
		printf("%5zu\t", index);
	} // end for print header

	for(size_t index = 0; index < RAM_SIZE; index++)
	{
		if (index % 10 == 0)
		{
			printf("\n%zu\t", index);
		} // end if new string begin

		printf("%+05d\t",memory[index]);
	} // end for data output
	puts("");
} // end function showMemoryDump
