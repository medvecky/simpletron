#include <stdio.h>
#include <string.h>

#define FILENAME_LENGTH 50

FILE *openSourceFile(FILE *outputFile)
{
	char fileName[FILENAME_LENGTH];
	
	FILE *sourceFile;

	printf("%s: ", "Enter sml program file name" );
	
	fgets(fileName,sizeof(fileName), stdin);
	fileName[strcspn(fileName,"\n")] = 0;
	
	if ((sourceFile = fopen(fileName,"r")) == NULL)
	{
		puts("*** ERROR ***");
		printf("Can't open file %s\n", fileName);
		puts("*** SIMPLETRON TERMINATED ***");

		fputs("*** ERROR ***\n", outputFile);
		fprintf(outputFile,"Can't open file %s\n", fileName);
		fputs("*** SIMPLETRON TERMINATED ***\n", outputFile);
        } // end if try open file

	return sourceFile;
} // end function openSourceFile
