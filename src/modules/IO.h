#ifndef _IO_
#define _IO_

#include <stdbool.h>
#include <stdio.h>

void IO_showWelcomeMessage(FILE *outputFile);
bool IO_readProgram(int *memory, FILE *outputFile);
void IO_showMemoryDump(int *memory, FILE *outputFile);
void IO_showEmptyLine(FILE *outputFile);	
void IO_showExecutionBeginsMessage(FILE *outputFile);
void IO_showExecutionTerminatedMessage(FILE *outputFile);
void IO_showInputPrompt();
void IO_showOutOfMemoryMessage(FILE *outputFile);
void IO_showMessageInvalidCommand(int operationCode, int instructionCounter, FILE *outputFile);
void IO_showMessageCantOpenOutputFile();
void IO_showCpuDump();
void IO_showOutOfLimitErrorMessage(FILE *ouputFile);
int IO_getValidDataWord(FILE *outputFile);
#endif
