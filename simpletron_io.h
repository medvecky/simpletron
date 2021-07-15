#ifndef _SIMPLETRON_IO_
#define _SIMPLETRON_IO_

void showWelcomeMessage();
void readProgramFromConsole(int *memory);
void showMemoryDump(int *memory);
void showEmptyLine();	
void showExecutionBeginsMessage();
void showExecutionTerminatedMessage();
int getDataWord();
void showDataWord(int dataWord);

#define INPUT_BREAK_MARKER -99999

#endif
