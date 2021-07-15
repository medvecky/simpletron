#include <stdio.h>

#include "simpletron_cpu.h"
#include "simpletron_memory.h"
#include "simpletron_io.h"

//CPU commands
#define HALT 43

#define READ 10 	// Read a word from the terminal into 
					//a specific location in memory

#define WRITE 11	//Write a word from specific location
					//in memory to the terminal

static int accumulator = 0;
static size_t instructionCounter = 0;
static int instructionRegister = 0;
static int operationCode = 0;
static int operand = 0;

static void read(int * memory, size_t address);
static void write(int * memory, size_t address);

void executeProgram(int *memory)
{
	accumulator = 0;
	instructionCounter = 0;
	instructionRegister = 0;
	operationCode = 0;
	operand = 0;

	showExecutionBeginsMessage();

	while (instructionCounter < MEMORY_SIZE  && operationCode != HALT)
	{	
		instructionRegister = memoryRead(memory, instructionCounter);
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		
		switch (operationCode)
		{
			case READ: 
				read(memory, operand);
				break;
			case WRITE :
				write(memory, operand);
				break;
		} //end switch operation code

		instructionCounter++;

	} // end while main loop

	showExecutionTerminatedMessage();
} // end function execute progam

int getCpuAccumulator()
{
	return accumulator;
} // end function getCpuAccumulator

size_t getCpuInstructionCounter()
{
	return instructionCounter;
} // end function getCpuInstructionCounter

int getCpuInstructionRegister()
{
	return instructionRegister;
} // end function getCpuInstructionRegister

int getCpuOperand()
{
	return operand;
} // end function getCpuOperand

int getCpuOperationCode()
{
	return operationCode;
} // end function getCpuOperationCode

static void read(int * memory, size_t address)
{
	memoryWrite(memory, address, getDataWord());	
} // end function read

static void write(int * memory, size_t address)
{
	showDataWord(memoryRead(memory, address));	
} // end function write
