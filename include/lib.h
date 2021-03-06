#ifndef LIB_H
#define LIB_H

#include <types.h>

void * memset(void *start, int c, size_t n);
void * memcpy(void * dst, const void * src, size_t n);
char * itoa(int value, char * str, int base);

#endif  /* LIB_H */
