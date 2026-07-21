#ifndef VM_INCLUDE
#define VM_INCLUDE

#include <stdint.h>

#define STACK_SIZE 256
#define CODE_ARRAY_SIZE 256
#define CONST_POOL_SIZE 256

typedef enum 
{
	RET,
	PUSHB,
	POPB,
	ADD,
	SUBS,
	NEG,
	MUL,
	DIV,
	POW,
	OUT
} OPCODE;

extern int16_t stack[STACK_SIZE];
extern int16_t constPool[CONST_POOL_SIZE];
extern uint8_t constIndex;
extern OPCODE byteCode[CODE_ARRAY_SIZE];

void execute();

#endif
