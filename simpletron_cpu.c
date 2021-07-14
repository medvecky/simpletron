#include <stdio.h>

#include "simpletron_cpu.h"
#include "simpletron_memory.h"
#include "simpletron_io.h"

static int accumulator = 0;
static size_t instructionCounter = 0;
static int instructionRegister = 0;
static int operationCode = 0;
static int operand = 0;

void executeProgram(int *memory)
{
	accumulator = 0;
	instructionCounter = 0;
	instructionRegister = 0;
	operationCode = 0;
	operand = 0;

	showExecutionBeginsMessage();

	while (instructionCounter < MEMORY_SIZE  && operationCode != 43)
	{	
		instructionRegister = memoryRead(memory, instructionCounter);
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		printf("counter: %zu\t operation: %d\t operand: %d\n", instructionCounter, operationCode, operand);
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
