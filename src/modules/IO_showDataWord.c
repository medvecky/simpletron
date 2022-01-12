#include <stdio.h>

void IO_showDataWord(int dataWord, FILE *outputFile)
{
	printf(" > %+05d\n", dataWord);
	fprintf(outputFile, " > %+05d\n", dataWord);
} // end function IO_showDataWord
