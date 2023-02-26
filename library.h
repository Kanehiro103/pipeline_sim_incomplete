#ifndef _LIBRARY_H_
#define _LIBRARY_H_

union fu { float f; unsigned int u; };

unsigned int cut(unsigned int, unsigned int, unsigned int);
unsigned long cut_ul(unsigned long, unsigned int, unsigned int);
float to_float(unsigned int);
unsigned int to_fpn(float);

// ここから
unsigned int pow2(unsigned int);
int to_signed(unsigned int, int);
unsigned int fpn(unsigned int, unsigned int, unsigned int);

#endif