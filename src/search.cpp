#include "token_array.h"
#include "tokenizer_main.h"
#include <time.h>

#define PRINT  printf(" %g, %d\n", x, y);

// Binary search revisited.
// Binary Search Code from http://eigenjoy.com/2011/09/09/binary-search-revisited/
// ASM adapted for Visual Studio 2012 by Eric Nam
// Return 1 << log_2(list_size-1), or 0 if list_size == 1.
// This sets the initial value of b in fbsearch().
inline unsigned init_bit( unsigned list_size )
{
    unsigned b;
    __asm {			push eax
					push ecx

					mov eax, list_size
					dec eax
					je DONE
					bsr ecx, eax // BSR - Bit Scan Reverse (386+)
					mov eax, 1
					shl eax, cl
					mov b, eax
				DONE: 
					pop eax
					pop ecx
	}
    return b;
}

// Return the greatest unsigned i where haystack[i] <= needle.
// If i does not exist (haystack is empty, or needle < haystack[0])
// then return unsigned(-1). T can be any type for which the binary
// operator <= is defined.
template <typename T>
unsigned fbsearch( const T haystack[], unsigned haystack_size,
                   const T& needle )
{
    if( haystack_size == 0 ) return unsigned(-1);
    unsigned i = 0;
    for( unsigned b = init_bit(haystack_size) ; b ; b >>= 1 )
    {
        unsigned j = i | b;
//		printf("Got haystack[%u] = %d with b = %u | ", j, haystack[j], b);
        if( haystack_size <= j ) continue;
        if( haystack[j] <= needle ) i = j;
        else
        {
            for( b >>= 1 ; b ; b >>= 1 ) {
                if( haystack[i|b] <= needle ) i |= b;
//						printf("Got haystack[%u] = %d with b = %u | ", i, haystack[i], b);
				}
            break;
        }
    }
    return i || *haystack <= needle ? i : unsigned(-1);
}

// Fast but approach only works for ranges in ascii
int isMyAlpha_InEq (int c) { return((c >='a' && c <='z') || (c >='A' && c <='Z')); }
int isNotMyAlpha_InEq (int c) { return((c <'a' || c >'z') && (c <'A' || c >'Z')); }

// Simple Linear Search (Sorted order)
int isMyAlpha_linear(char * a, char c) {
	for (unsigned char i = 0; i < POS_LOOKUP_LEN; i++) {
		if (c == a[i])
			return true;
	}
	return false;
}

// Simple Linear Search (Sorted order)
int isNotMyAlpha_linear(char * a, char c) {
	for (unsigned char i = 0; i < NEG_LOOKUP_LEN; i++)
		if (c == a[i])
			return true;
	return false;
}

// Binary Search
int isMyAlpha_bsearch (char * a, char c) {
	int result = fbsearch(a, POS_LOOKUP_LEN, c);
//	printf("B-search result: %c matching %c\n", a[result], c);
	return result != -1 && a[result] == c;
}

// Binary Search
int isNotMyAlpha_bsearch (char * a, char c) {
	int result = fbsearch(a, NEG_LOOKUP_LEN, c);
//	printf("B-search result: %c matching %c\n", a[result], c);
	return result != -1 && a[result] == c;
}

void positive_tokenizer_linear (FILE* fp)
{
	int c = 0,wc = 0;
	std::string cur_token = "";
	clock_t begin, end;
	double time_spent;	

	char* a = create_sorted_pos_array();
	while (isspace(c=getc(fp)));
	ungetc(c,fp);
	begin = clock();
	while((c = getc(fp)) != EOF)
	{
		if (isMyAlpha_linear(a, c)){
			cur_token += c;
		}
		else
		{
			if (cur_token != "") {
//				printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
				wc++;
			}
			cur_token = c;

//			printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
			wc++;
			cur_token = "";
		}
	}
	if (cur_token != "") {
//		printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
		wc++;
	}
	end = clock();
	close_token_array(a);
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Positive Linear Elapsed: %f seconds, %d tokens found\n", time_spent, wc);
}

void positive_tokenizer_bsearch (FILE* fp)
{
	int c = 0,wc = 0;
	std::string cur_token = "";
	clock_t begin, end;
	double time_spent;	

	char* a = create_sorted_pos_array();
	while (isspace(c=getc(fp)));
	ungetc(c,fp);
	begin = clock();
	while((c = getc(fp)) != EOF)
	{
		if (isMyAlpha_bsearch(a, c)){
			cur_token += c;
		}
		else
		{
			if (cur_token != "") {
//				printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
				wc++;
			}
			cur_token = c;

//			printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
			wc++;
			cur_token = "";
		}
	}
	if (cur_token != "") {
//		printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
		wc++;
	}
	end = clock();
	close_token_array(a);
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Positive Bsearch Elapsed: %f seconds, %d tokens found\n", time_spent, wc);
}

void negative_tokenizer_linear (FILE* fp)
{
	int c = 0,wc = 0;
	std::string cur_token = "";
	clock_t begin, end;
	double time_spent;	

	char* a = create_sorted_neg_array();

	while (isspace(c=getc(fp)));
	ungetc(c,fp);
	begin = clock();
	while((c = getc(fp)) != EOF)
	{
		if (isNotMyAlpha_linear(a, c))
		{
			if (cur_token != "") {
//				printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
				wc++;
			}
			cur_token = c;

//			printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
			wc++;
			cur_token = "";
		}
		else
		{
			cur_token+=c;
		}
	}
	if (cur_token != "") {
//		printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
		wc++;
	}
	end = clock();
	close_token_array(a);
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Negative Linear Elapsed: %f seconds, %d tokens found\n", time_spent, wc);
}

void negative_tokenizer_bsearch (FILE* fp)
{
	int c = 0,wc = 0;
	std::string cur_token = "";
	clock_t begin, end;
	double time_spent;	

	char* a = create_sorted_neg_array();

	while (isspace(c=getc(fp)));
	ungetc(c,fp);
	begin = clock();
	while((c = getc(fp)) != EOF)
	{
		if (isNotMyAlpha_bsearch(a, c))
		{
			if (cur_token != "") {
//				printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
				wc++;
			}
			cur_token = c;

//			printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
			wc++;
			cur_token = "";
		}
		else
		{
			cur_token+=c;
		}
	}
	if (cur_token != "") {
//		printf("Token[%d] = \"%s\"\n", wc, cur_token.c_str());
		wc++;
	}
	end = clock();
	close_token_array(a);
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Negative Bsearch Elapsed: %f seconds, %d tokens found\n", time_spent, wc);
}

//void * binary_search(
//	register const void *key,
//	const void *base0,
//	size_t nmemb,
//	register size_t size,
//	register int (*compar)(const void *, const void *)) {
//
//	register const char *base = (char *) base0;
//	register size_t lim;
//	register int cmp;
//	register const void *p;
//	for (lim = nmemb; lim != 0; lim >>= 1) {
//		p = base + (lim >> 1) * size;
//		cmp = (*compar)(key, p);
//		if (cmp == 0)
//			return ((void *)p);
//		if (cmp > 0) {	/* key > p: move right */
//			base = (char *)p + size;
//			lim--;
//		}		/* else move left */
//	}
//	return (NULL);
//}