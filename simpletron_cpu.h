#ifndef _SIMPLETRON_CPU_
#define _SIMPLETRON_CPU_

void showCpuDump();
void executeProgram(int *memory);
int getCpuAccumulator();
size_t getCpuInstructionCounter();
int getCpuInstructionRegister();
int getCpuOperand();
int getCpuOperationCode();

#endif
