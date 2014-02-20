#ifndef TYPES_H
#define TYPES_H

// Explicitly-sized versions of integer types
typedef __signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef uint8_t bool;
#define true 1;
#define false 0;

// size_t is used for memory object sizes.
typedef uint32_t size_t;

#endif /* TYPES_H */
