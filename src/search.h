#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string>

void positive_tokenizer_linear (FILE* fp);
void negative_tokenizer_linear (FILE* fp);
void positive_tokenizer_bsearch (FILE* fp);
void negative_tokenizer_bsearch (FILE* fp);

#endif