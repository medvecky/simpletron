#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "simpletron_io.h"
#include "simpletron_memory.h"
#include "simpletron_cpu.h"

#define ERROR_VALUE 55555
#define WORD_SIZE 4 

static bool readProgramFromFile(int *memory, FILE *sourceFile, FILE *outputFile);
static FILE *openSourceFile(FILE *outputFile);
static int parseInputString(char *buffer);
static bool isInputStringValid(char *buffer);

void showWelcomeMessage(FILE *outputFile)
{
	puts("*** Welcome to Simpletron! ***");
	fputs("*** Welcome to Simpletron! ***\n",outputFile);
} // end function showWelcomeMessage

bool readProgram(int *memory, FILE *outputFile)
{
	FILE * sourceFile = openSourceFile(outputFile);
	
	if(sourceFile == NULL)
	{	
		return false; 		
	} // end if chek file is opened

	if (!readProgramFromFile(memory, sourceFile, outputFile))
	{
		fclose(sourceFile);
		return false;
	} // end if readProgramFromFile result

	fclose(sourceFile);
	return true;

} // end function readProgram

static bool readProgramFromFile(int *memory, FILE *sourceFile, FILE *outputFile)
{
	size_t wordCounter = 0;
	int dataWord;
	
	char buffer[20];
	
	while(fgets(buffer, sizeof(buffer), sourceFile) != NULL)
	{
		buffer[strcspn(buffer,"\n")] = 0;
		int dataWord = parseInputString(buffer);
		if (dataWord == ERROR_VALUE)
		{
			puts("*** FATAL ERROR ***");
			printf("Invalid token %s, string %zu\n", buffer, wordCounter + 1);

			fputs("*** FATAL ERROR ***\n", outputFile);
			fprintf(outputFile, "Invalid token %s, string %zu\n", buffer, wordCounter + 1);
			
			return false;
		} // end if check parsing result 

		if (dataWord < LOW_DATA_LIMIT || dataWord > HIGH_DATA_LIMIT)
		{
			puts("*** FATAL ERROR ***");
			puts("*** Data word out of limits  ***");
			printf(" %d, string %zu\n", dataWord, wordCounter + 1);

			fputs("*** FATAL ERROR ***\n", outputFile);
			fputs("*** Data word out of limits  ***\n", outputFile);
			fprintf(outputFile, " %d, string %zu\n", dataWord, wordCounter + 1);
			
			return false;
		} // end if dataWord limit check
		
		memoryWrite(memory, wordCounter++, dataWord);
	} // end while data from file read loop

	puts("*** Program loading completed. ***");

	fputs("*** Program loading completed. ***\n", outputFile);
	
	return true;
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

int getValidDataWord(FILE *outputFile)
{
	int dataWord = getDataWord();

	while (dataWord < LOW_DATA_LIMIT || dataWord > HIGH_DATA_LIMIT)
	{

		showOutOfLimitErrorMessage(outputFile);
		printf(" %c ", '?');
		dataWord = getDataWord();
	} // end while limit check

	return dataWord;
} // end function getValidDataWord

void showMemoryDump(int *memory, FILE *outputFile)
{
	puts("MEMORY:");
	fputs("MEMORY:\n", outputFile);
	printf("%c\t", ' ' );
	fprintf(outputFile, "%c\t", ' ' );
	for (size_t index = 0; index < 10; index++)
	{
		printf("%5zu\t", index);
		fprintf(outputFile, "%5zu\t", index);
	} // end for print header

	for(size_t index = 0; index < MEMORY_SIZE; index++)
	{
		if (index % 10 == 0)
		{
			printf("\n%zu\t", index);
			fprintf(outputFile, "\n%zu\t", index);
		} // end if new string begin

		printf("%+05d\t",memory[index]);
		fprintf(outputFile, "%+05d\t",memory[index]);
	} // end for data output
	puts("");
	fputs("\n", outputFile);
} // end function showMemoryDump

void showEmptyLine(FILE *outputFile)
{
	puts("");
	fputs("\n", outputFile);
} // end function showEmptyLine

void showExecutionBeginsMessage(FILE *outputFile)
{
	puts("*** Program execution begins. ***");
	fputs("*** Program execution begins. ***\n",outputFile);
} // end function showExecutionBeginsMessage

void showExecutionTerminatedMessage(FILE *outputFile)
{
	puts("*** Simpletron execution terminated ***");	
	fputs("*** Simpletron execution terminated ***\n", outputFile);	
} // end function showExecutionTerminatedMessage

void showCpuDump(FILE *outputFile)
{
	puts("REGISTERS:");
	printf("accumulator:\t\t\t%+05d\n", getCpuAccumulator());
	printf("instrcutionCounter:\t\t   %02zu\n", getCpuInstructionCounter());
	printf("instructionRegister:\t\t%+05d\n", getCpuInstructionRegister());
	printf("operationCode:\t\t\t   %02d\n", getCpuOperationCode());
	printf("operand:\t\t\t   %02d\n", getCpuOperand());

	fputs("REGISTERS:\n", outputFile);
	fprintf(outputFile, "accumulator:\t\t\t%+05d\n", getCpuAccumulator());
	fprintf(outputFile, "instrcutionCounter:\t\t   %02zu\n", getCpuInstructionCounter());
	fprintf(outputFile, "instructionRegister:\t\t%+05d\n", getCpuInstructionRegister());
	fprintf(outputFile, "operationCode:\t\t\t   %02d\n", getCpuOperationCode());
	fprintf(outputFile, "operand:\t\t\t   %02d\n", getCpuOperand());
} // end function showCpuDump

void showDataWord(int dataWord, FILE *outputFile)
{
	printf(" > %+05d\n", dataWord);
	fprintf(outputFile, " > %+05d\n", dataWord);
} // end function showDataWord

void showInputPrompt()
{
	printf("%s", " ? ");
} // end function showInputPromt

void showOutOfLimitErrorMessage(FILE *outputFile)
{
	puts("*** Entered data is out of limits ***");
	fputs("*** Entered data is out of limits ***\n", outputFile);
} // end of showOutOfLimitErrorMessage

void showAccumulatorOverflowMessage(FILE *outputFile)
{
	puts("*** FATAL ERROR  ***");
	puts("*** accumulator overflow  ***");

	fputs("*** FATAL ERROR  ***\n", outputFile);
	fputs("*** accumulator overflow  ***\n", outputFile);
} // end function showAccumulatorOverflowMessage

void showOutOfMemoryMessage(FILE *outputFile)
{
	puts("*** FATAL ERROR  ***");
	puts("*** memory overflow  ***");

	fputs("*** FATAL ERROR  ***\n", outputFile);
	fputs("*** memory overflow  ***\n", outputFile);
} // end function showOutOfMemory

void showDivideByZeroMessage(FILE *outputFile)
{
	puts("*** FATAL ERROR  ***");
	puts("*** Attempt to divide by zero***");

	fputs("*** FATAL ERROR  ***\n", outputFile);
	fputs("*** Attempt to divide by zero***\n", outputFile);
} // end function showDivideByZeroMessage

static FILE *openSourceFile(FILE *outputFile)
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

		fputs("*** ERROR ***\n", outputFile);
		fprintf(outputFile,"Can't open file %s\n", fileName);
		fputs("*** SIMPLETRON TERMINATED ***\n", outputFile);
} // end if try open file

	return sourceFile;
} // end function openSourceFile

void showMessageInvalidCommand(int operationCode, int instructionCounter, FILE *outputFile)
{
	puts("*** FATAL ERROR ***");
	printf("Illegal operation %d on address %02d\n", operationCode, instructionCounter);

	fputs("*** FATAL ERROR ***\n", outputFile);
	fprintf(outputFile, "Illegal operation %d on address %02d\n", operationCode, instructionCounter);
} // end function showMessageInvalidCommand

static int parseInputString(char *buffer)
{
	char *remainderPtr;

	if (isInputStringValid(buffer))
	{
		return strtoul(buffer, &remainderPtr, 0); 
	} // end if string validation 

	return ERROR_VALUE;
} // end function parseInputString

static bool isInputStringValid(char *buffer)
{
	if (strlen(buffer) != WORD_SIZE)
	{
		return false;		
	} // end if chek buffer length

	for (size_t index = 0; index < WORD_SIZE; index++)
	{
		if (!isdigit(buffer[index]))
		{
			return false;
		} // end if check is symbol digit 
	} // end for check all symbols are numbers

	return true;
} // end function isInputStringValid

void showMessageCantOpenOutputFile()
{
	puts("*** ERROR ***");
	puts("*** Can't open output file ***");
	puts("*** SIMPLETRON TERMINATED ***");
} // end function showMessageCantOpenOutputFile();

