#ifndef COMMON_HEADER
#define COMMON_HEADER

#include <stdio.h>

#define error(msg) fprintf(stderr, "%s\n", msg)

enum ERRORS
{
    EX_USAGE=64,
    MEM_ALLOC=10,
    MISSING_TOKEN=11,
    UKNOWN_STATEMENT=12
};

#endif
