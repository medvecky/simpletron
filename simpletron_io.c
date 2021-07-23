#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simpletron_io.h"
#include "simpletron_memory.h"
#include "simpletron_cpu.h"

static void readProgramFromFile(int *memory, FILE *sourceFile);

static FILE *openSourceFile();

void showWelcomeMessage()
{
	puts("*** Welcome to Simpletron! ***");
} // end function showWelcomeMessage

bool readProgram(int *memory)
{
	FILE * sourceFile = openSourceFile();
	
	if(sourceFile == NULL)
	{
		return false; 		
	} // end if chek file is opened

	readProgramFromFile(memory, sourceFile);

	fclose(sourceFile);
	return true;

} // end function readProgram

static void readProgramFromFile(int *memory, FILE *sourceFile)
{
	size_t wordCounter = 0;
	int dataWord;
	
	char buffer[20];
	
	while(fgets(buffer, sizeof(buffer), sourceFile) != NULL)
	{
		printf("%zu ", wordCounter++);	
		buffer[strcspn(buffer,"\n")] = 0;
		puts(buffer);
		buffer[0] = 0;
	} // end while data from file read loop

//	while((dataWord = getDataWord()) != INPUT_BREAK_MARKER && wordCounter < MEMORY_SIZE)
//	{
//		if (dataWord < LOW_DATA_LIMIT || dataWord > HIGH_DATA_LIMIT)
//		{
//			showOutOfLimitErrorMessage();
//			printf("%02zu ? ", wordCounter);
//			continue;
//		} // end if limit check
//		memoryWrite(memory, wordCounter++, dataWord);
//		printf("%02zu ? ", wordCounter);
//	} // end while readData loop
//
//	puts("*** Program loading completed. ***");
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

static FILE *openSourceFile()
{
	char fileName[50];
	
	FILE *sourceFile;

	printf("%s: ", "Enter sml program file name" );
	
	fgets(fileName,sizeof(fileName), stdin);
	fileName[strcspn(fileName,"\n")] = 0;
	
	if ((sourceFile = fopen(fileName,"r")) == NULL)
	{
		puts("*** ERROR ***");
		printf("Can't open file %s\n", fileName);
		puts("*** SIMPLETRON TERMINATED ***");
	} // end if try open file

	return sourceFile;
} // end function openSourceFile
