#include <stdio.h>
#include <stdlib.h>

#include "simpletron_io.h"
#include "simpletron_memory.h"
#include "simpletron_cpu.h"

void showWelcomeMessage()
{
	puts("*** Welcome to Simpletron! ***");
	puts("*** Please enter your program one instruction ***");
	puts("*** (or data word) at a time. I will type the ***");
	puts("*** location number and question mark (?).    ***");
	puts("*** You then type word for that location. ***");
	puts("*** Type the sentinel -99999 to stop entering ***");
	puts("*** your program.  ***");
} // end function showWelcomeMessage

void  readProgramFromConsole(int *memory)
{
	size_t wordCounter = 0;
	int dataWord;
	
	printf("%02zu ? ", wordCounter);
	while((dataWord = getDataWord()) != INPUT_BREAK_MARKER && wordCounter < MEMORY_SIZE)
	{
		if (dataWord < LOW_DATA_LIMIT || dataWord > HIGH_DATA_LIMIT)
		{
			showOutOfLimitErrorMessage();
			printf("%02zu ? ", wordCounter);
			continue;
		} // end if limit check
		memoryWrite(memory, wordCounter++, dataWord);
		printf("%02zu ? ", wordCounter);
	} // end while readData loop

	puts("*** Program loading completed. ***");
} // end function readProgramfromConsole

int getDataWord()
{
	int dataWord;

	while(scanf("%d", &dataWord) != 1) 
	{
		while (getchar() != '\n');
		puts("Invalid data format.");
		puts("Please enter correct data word");
		printf(" %c ", '?');
	} // end while read data end validation
	while (getchar() != '\n');
	return dataWord;
} // end function getDataWord

int getValidDataWord()
{
	int dataWord = getDataWord();

	while (dataWord < LOW_DATA_LIMIT || dataWord > HIGH_DATA_LIMIT)
	{

		showOutOfLimitErrorMessage();
		printf(" %c ", '?');
		dataWord = getDataWord();
	} // end while limit check

	return dataWord;
} // end function getValidDataWord

void showMemoryDump(int *memory)
{
	puts("MEMORY:");
	
	printf("%c\t", ' ' );
	for (size_t index = 0; index < 10; index++)
	{
		printf("%5zu\t", index);
	} // end for print header

	for(size_t index = 0; index < MEMORY_SIZE; index++)
	{
		if (index % 10 == 0)
		{
			printf("\n%zu\t", index);
		} // end if new string begin

		printf("%+05d\t",memory[index]);
	} // end for data output
	puts("");
} // end function showMemoryDump

void showEmptyLine()
{
	puts("");
} // end function showEmptyLine

void showExecutionBeginsMessage()
{
	puts("*** Program execution begins. ***");
} // end function showExecutionBeginsMessage

void showExecutionTerminatedMessage()
{
	puts("*** Simpletron execution terminated ***");	
} // end function showExecutionTerminatedMessage

void showCpuDump()
{
	puts("REGISTERS:");
	printf("accumulator:\t\t\t%+05d\n", getCpuAccumulator());
	printf("instrcutionCounter:\t\t   %02zu\n", getCpuInstructionCounter());
	printf("instructionRegister:\t\t%+05d\n", getCpuInstructionRegister());
	printf("operationCode:\t\t\t   %02d\n", getCpuOperationCode());
	printf("operand:\t\t\t   %02d\n", getCpuOperand());
} // end function showCpuDump

void showDataWord(int dataWord)
{
	printf(" > %+05d\n", dataWord);
} // end function showDataWord

void showInputPrompt()
{
	printf("%s", " ? ");
} // end function showInputPromt

void showOutOfLimitErrorMessage()
{
	puts("*** Entered data is out of limits ***");
} // end of showOutOfLimitErrorMessage

void showAccumulatorOverflowMessage()
{
	puts("*** FATAL ERROR  ***");
	puts("*** accumulator overflow  ***");
} // end function showAccumulatorOverflowMessage

void showOutOfMemoryMessage()
{
	puts("*** FATAL ERROR  ***");
	puts("*** memory overflow  ***");
} // end function showOutOfMemory

void showDivideByZeroMessage()
{
	puts("*** FATAL ERROR  ***");
	puts("*** Attempt to divide by zero***");
} // end function showDivideByZeroMessage

void showMessageInvalidCommand(int operationCode, int instructionCounter)
{
	puts("*** FATAL ERROR ***");
	printf("Illegal operation %d on address %02d\n", operationCode, instructionCounter);
} // end function showMessageInvalidCommand

