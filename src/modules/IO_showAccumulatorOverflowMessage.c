#include <stdio.h>

void IO_showAccumulatorOverflowMessage(FILE *outputFile)
{
	puts("*** FATAL ERROR  ***");
	puts("*** accumulator overflow  ***");

	fputs("*** FATAL ERROR  ***\n", outputFile);
	fputs("*** accumulator overflow  ***\n", outputFile);
} // end function IO_showAccumulatorOverflowMessage
