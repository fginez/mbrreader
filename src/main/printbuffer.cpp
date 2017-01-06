#include <stdio.h>
#include "printbuffer.h"

void print_chars(const unsigned char *in, const unsigned int len)
{
    int i;
    for (i=0; (unsigned int)i<len; i++)
        printf("%c", in[i]);    
}

void print_hex(const unsigned char *in, const unsigned int len)
{
    int i;
    for (i=0; (unsigned int)i<len; i++)
        printf("%02.2X", in[i]);
}



void print_hex_dump2(const unsigned char * in, const unsigned int len, const unsigned int col, const char* pre) {
	unsigned char* ptr = (unsigned char*) in;
	int currCol = 0;

	do {
		if ( 0 == currCol ) {
			printf("%s", pre);
		}
		printf("%02.2X", *ptr);
		currCol++;
		ptr++;
		if ( currCol & (currCol % col) ) {
			printf(" ");
		} else {
			if ( ptr < (in+len) ) {
				printf("\n");
				currCol = 0;
			}
		}
	} while ( ptr < (in+len) );
	printf("\n");
}

void print_hex_dump(const unsigned char * in, const unsigned int len, const unsigned int col) {
	print_hex_dump2(in, len, col, "");
}
