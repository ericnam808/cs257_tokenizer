#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string>
#include "tokenizer_main.h"
#include "search.h"

FILE *fp, *ofp;
unsigned int POS_LOOKUP_LEN = strlen(PERMISSIBLE);
unsigned int NEG_LOOKUP_LEN = 256 - POS_LOOKUP_LEN;

int main (int argc, char *argv[]) 
{
	int c=1;
	if(argc == 1)	//no arguments, use standard input and output
	{
		fp = stdin;
	}
	while (argc > 1 || (fp == stdin && (c = getc(fp)) != EOF))
	{
		if (fp == stdin) ungetc(c, fp);
		++argv;
		if (fp != stdin) fp = fopen(*argv, "r");
		if (fp == NULL)
		{
			printf("Can't open %s\n", *argv);
			return(1);
		}
		else {
			printf("Positive lookup array size: %d characters\n", POS_LOOKUP_LEN);
			printf("Negative lookup array size: %d characters\n", NEG_LOOKUP_LEN);
			positive_tokenizer_linear(fp);
			rewind(fp);
			negative_tokenizer_linear(fp);
			rewind(fp);
			positive_tokenizer_bsearch(fp);
			rewind(fp);
			negative_tokenizer_bsearch(fp);
			if (fp != stdin) fclose(fp);
		}
		argc--;

	}

	return(0); 
}