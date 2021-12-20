#ifndef _CPU_
#define _CPU_

#include <stdio.h>

#define HIGH_DATA_LIMIT 9999
#define LOW_DATA_LIMIT -9999

void CPU_executeProgram(int *memory, FILE *outputFile);
int CPU_getAccumulator();
size_t CPU_getInstructionCounter();
int CPU_getInstructionRegister();
int CPU_getOperand();
int CPU_getOperationCode();

#endif
