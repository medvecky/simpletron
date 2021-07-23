#ifndef _SIMPLETRON_IO_
#define _SIMPLETRON_IO_

#include <stdbool.h>

void showWelcomeMessage();
bool readProgram(int *memory);
void showMemoryDump(int *memory);
void showEmptyLine();	
void showExecutionBeginsMessage();
void showExecutionTerminatedMessage();
int getValidDataWord();
int getDataWord();
void showDataWord(int dataWord);
void showInputPrompt();
void showOutOfLimitErrorMessage();
void showAccumulatorOverflowMessage();
void showOutOfMemoryMessage();
void showDivideByZeroMessage();

#define INPUT_BREAK_MARKER -99999

#endif
