#ifndef _SIMPLETRON_CPU_
#define _SIMPLETRON_CPU_

#define HIGH_DATA_LIMIT 9999
#define LOW_DATA_LIMIT -9999

void showCpuDump();
void executeProgram(int *memory, FILE *outputFile);
int getCpuAccumulator();
size_t getCpuInstructionCounter();
int getCpuInstructionRegister();
int getCpuOperand();
int getCpuOperationCode();

#endif
