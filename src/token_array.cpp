#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string>
#include "token_array.h"
#include "tokenizer_main.h"

// Comparator Function
int cmpfunc (const void * a, const void * b)
{
   return ( *(char*)a - *(char*)b );
}

// Create Positive
char * create_sorted_pos_array()
{
	char * token_array = new char [POS_LOOKUP_LEN];
	memcpy(token_array, PERMISSIBLE, POS_LOOKUP_LEN);
	qsort(token_array, POS_LOOKUP_LEN, sizeof(char), cmpfunc);
	return token_array;
}

// Create Negative
char * create_sorted_neg_array()
{
	char * token_array = new char [NEG_LOOKUP_LEN];
	unsigned char j = 0;
	for(unsigned char i = 0; i < NEG_LOOKUP_LEN; i++)
	{
		while (j < 256 && strrchr(PERMISSIBLE, (char)j) != NULL) {
			j++;
		}
		token_array[i] = j;
		j++;
	}

	qsort(token_array, NEG_LOOKUP_LEN, sizeof(char), cmpfunc);
	return token_array;
}

// Close
void close_token_array(char * token_array)
{
	free(token_array);
	token_array = NULL;
}