#ifndef _SIMPLETRON_IO_
#define _SIMPLETRON_IO_

#include <stdbool.h>

void showWelcomeMessage(FILE *outputFile);
bool readProgram(int *memory, FILE *outputFile);
void showMemoryDump(int *memory, FILE *outputFile);
void showEmptyLine(FILE *outputFile);	
void showExecutionBeginsMessage(FILE *outputFile);
void showExecutionTerminatedMessage(FILE *outputFile);
int getValidDataWord(FILE *outputFile);
int getDataWord();
void showDataWord(int dataWord, FILE *outputFile);
void showInputPrompt();
void showOutOfLimitErrorMessage(FILE *ouputFile);
void showAccumulatorOverflowMessage(FILE *ouputFile);
void showOutOfMemoryMessage(FILE *outputFile);
void showDivideByZeroMessage(FILE *outputFile);
void showMessageInvalidCommand(int operationCode, int instructionCounter, FILE *outputFile);
void showMessageCantOpenOutputFile();

#endif
