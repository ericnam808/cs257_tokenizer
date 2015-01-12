#ifndef TOKENIZER_MAIN_H
#define TOKENIZER_MAIN_H
#include <stdio.h>
#include <string>

int ungetc(int, FILE *);

const char PERMISSIBLE[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
extern unsigned int POS_LOOKUP_LEN;
extern unsigned int NEG_LOOKUP_LEN;

#endif
