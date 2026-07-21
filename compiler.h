#include <stdint.h>

#ifndef COMPILER_HEADER
#define COMPILER_HEADER

typedef enum
{
    NONE_PREC=1,
    ADD_PREC=2,
    SUBS_PREC=2,
    MUL_PREC=3,
    DIV_PREC=3,
    POW_PREC=4,
    LPAREN_PREC=5,
    RPAREN_PREC=0
} PRECEDENCE;

static void expression(const char*, PRECEDENCE);
void compile();
extern char* source;
extern uint8_t sourceIndex;

#endif
