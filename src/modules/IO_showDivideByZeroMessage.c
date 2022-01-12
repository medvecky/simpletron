#include <stdio.h>

void IO_showDivideByZeroMessage(FILE *outputFile)
{
	puts("*** FATAL ERROR  ***");
	puts("*** Attempt to divide by zero***");

	fputs("*** FATAL ERROR  ***\n", outputFile);
	fputs("*** Attempt to divide by zero***\n", outputFile);
} // end function IO_showDivideByZeroMessage
