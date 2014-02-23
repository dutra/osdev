#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

void puts(char *string);
void printf(const char *string, const void *args, ...);

#endif /* STDIO_H */
