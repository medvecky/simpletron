#include <stdio.h>
#include <stdbool.h>

#include "simpletron_cpu.h"
#include "simpletron_memory.h"
#include "simpletron_io.h"


//CPU commands
#define HALT 43

#define READ 10 		// Read a word from the terminal into 
						// a specific location in memory

#define WRITE 11		// Write a word from specific location
						//in memory to the terminal

#define LOAD 20			// Load a word from a specific memory location 
		   				// into accumulator

#define STORE 21		// Store a word from accumulator into
						// a specific location in memory
					
#define ADD 30 			// Add word from specific memory location 
						// to accumulator

#define SUBSTRACT 31	// Substract  word from specific memory location 
						// from accumulator

#define DIVIDE 32		// Devide a word from accumulator 
						// by word from specific memory location 

#define MULTIPLY 33		// Multiply a word from accumulator 
						// by word from specific memory location 

#define BRANCH 40		// Branch to a specific location in memory

#define BRANCHNEG 41	// Branch to a specific location in memory if 
						// the accumulator is negative

#define BRANCHZERO 42	// Branch to a specific location in memory if 
						// the accumulator is zero

static int accumulator = 0;
static size_t instructionCounter = 0;
static int instructionRegister = 0;
static int operationCode = 0;
static int operand = 0;
static bool overflowFlag = false;

static void read(int * memory, size_t address, FILE *outputFile);
static void write(int * memory, size_t address, FILE *outputFIle);
static void load(int * memory, size_t address);
static void store(int * memory, size_t address);
static void add(int * memory, size_t address);
static void substract(int *memory, size_t address);
static void divide(int *memory, size_t address, FILE *outputFile);
static void multiply(int *memory, size_t address);
static void branch();
static void branchneg();
static void branchzero();
static bool isAccumulatorOverflow();
static void checkAccumulatorOverflow();
static void goToValidLocation();

void executeProgram(int *memory, FILE *outputFile)

{
	accumulator = 0;
	instructionCounter = 0;
	instructionRegister = 0;
	operationCode = 0;
	operand = 0;
	overflowFlag = false;

	showExecutionBeginsMessage(outputFile);

	while (instructionCounter < MEMORY_SIZE  && operationCode != HALT && !overflowFlag)
	{	
		instructionRegister = memoryRead(memory, instructionCounter);
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		
		switch (operationCode)
		{
			case READ: 
				read(memory, operand, outputFile);
				break;
			case WRITE :
				write(memory, operand, outputFile);
				break;
			case LOAD:
				load(memory, operand);
				break;
			case STORE:
				store(memory, operand);
				break;
			case ADD:
				add(memory, operand);
				break;
			case SUBSTRACT:
				substract(memory, operand);
				break;
			case DIVIDE:
				divide(memory, operand, outputFile);
				break;
			case MULTIPLY:
				multiply(memory, operand);
				break;
			case BRANCH:
				branch();
				continue;
			case BRANCHNEG:
				branchneg();
				continue;
			case BRANCHZERO:
				branchzero();
				continue;
			case HALT:
				break;
			default:
			  showMessageInvalidCommand(operationCode, instructionCounter, outputFile);
			  overflowFlag = true;
		} //end switch operation code

		instructionCounter++;

	} // end while main loop

	instructionCounter--;
	showExecutionTerminatedMessage(outputFile);

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

static void read(int * memory, size_t address, FILE *outputFile)
{
	showInputPrompt();
	memoryWrite(memory, address, getValidDataWord(outputFile));
} // end function read

static void write(int * memory, size_t address, FILE *outputFile)
{
	showDataWord(memoryRead(memory, address),outputFile);	
} // end function write

static void load(int * memory, size_t address)
{
	accumulator = memoryRead(memory, address);
} // end function load

static void store(int * memory, size_t address)
{
	memoryWrite(memory, address, accumulator);
} // end function store

static void add(int * memory, size_t address)
{
	accumulator += memoryRead(memory, address);
	checkAccumulatorOverflow();
} // end function add 

static void substract(int * memory, size_t address)
{
	accumulator -= memoryRead(memory, address);
	checkAccumulatorOverflow();
} // end function substract 

static void divide(int * memory, size_t address, FILE *outputFile)
{
	int divider = memoryRead(memory, address);
	if (divider == 0)
	{
		showDivideByZeroMessage(outputFile);
		overflowFlag = true;
		return;
	}
	accumulator /= divider; 
	checkAccumulatorOverflow();
} // end function divide 

static void multiply(int * memory, size_t address)
{
	accumulator *= memoryRead(memory, address);
	checkAccumulatorOverflow();
} // end function multiply 

static void branch()
{
	goToValidLocation();
} // end function branch

static void branchneg()
{
	if (accumulator < 0)
	{
		goToValidLocation();	
	} // end if check accumulator is negative 
	else 
	{
		instructionCounter++;
	} // end else if check accumulator negative
} // end function branchneg

static void branchzero()
{
	if (accumulator == 0)
	{
		goToValidLocation();
	} // end if check accumulator is zero
	else 
	{
		instructionCounter++;
	} // end else if check accumulator zero
} // end function branczero

static bool isAccumulatorOverflow()
{
	return (accumulator < LOW_DATA_LIMIT || accumulator > HIGH_DATA_LIMIT);
}

static void checkAccumulatorOverflow(FILE *outputFile)
{
	if (isAccumulatorOverflow())
	{
		showAccumulatorOverflowMessage(outputFile);
		overflowFlag = true;		
	} // end if checkOverflow
} // end function checkAccumulatorOverflow

static void goToValidLocation(FILE *outputFile)
{
	if (operand < MEMORY_SIZE)
	{
		instructionCounter = operand;
	}
	else
	{
		showOutOfMemoryMessage(outputFile);
		overflowFlag = true;
	} // end if else check memory limit
} // end function goToLocationWithValidation
