#ifndef __PRINTBUFFER_H_
#define __PRINTBUFFER_H_

void print_chars(const unsigned char *in, const unsigned int len);
void print_hex(const unsigned char *in, const unsigned int len);
void print_hex_dump (const unsigned char * in, const unsigned int len, const unsigned int col);
void print_hex_dump2(const unsigned char * in, const unsigned int len, const unsigned int col, const char* pre);
#endif
