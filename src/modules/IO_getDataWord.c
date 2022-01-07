#include <stdio.h>
#include <string.h>

int getDataWord()
{
	int dataWord;

	while(scanf("%d", &dataWord) != 1) 
	{
		while (getchar() != '\n');
		puts("Invalid data format.");
		puts("Please enter correct data word");
		printf(" %c ", '?');
	} // end while read data end validation

        while (getchar() != '\n');
	
        return dataWord;
} // end function getDataWord

