#include <stdio.h>

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

static void read(int * memory, size_t address);
static void write(int * memory, size_t address);
static void load(int * memory, size_t address);
static void store(int * memory, size_t address);
static void add(int * memory, size_t address);
static void substract(int *memory, size_t address);
static void divide(int *memory, size_t address);
static void multiply(int *memory, size_t address);
static void branch();
static void branchneg();
static void branchzero();

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
				divide(memory, operand);
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
		} //end switch operation code

		instructionCounter++;

	} // end while main loop

	instructionCounter--;
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
	showInputPrompt();
	memoryWrite(memory, address, getDataWord());	
} // end function read

static void write(int * memory, size_t address)
{
	showDataWord(memoryRead(memory, address));	
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
} // end function add 

static void substract(int * memory, size_t address)
{
	accumulator -= memoryRead(memory, address);
} // end function substract 

static void divide(int * memory, size_t address)
{
	accumulator /= memoryRead(memory, address);
} // end function divide 

static void multiply(int * memory, size_t address)
{
	accumulator *= memoryRead(memory, address);
} // end function multiply 

static void branch()
{
	instructionCounter = operand;
} // end function branch

static void branchneg()
{
	if (accumulator < 0)
	{
		instructionCounter = operand;
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
		instructionCounter = operand;
	} // end if check accumulator is zero
	else 
	{
		instructionCounter++;
	} // end else if check accumulator zero
} // end function branczero
