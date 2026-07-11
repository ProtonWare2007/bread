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
	MUL,
	DIV
} OPCODE;

uint8_t stack[STACK_SIZE];
uint8_t* stackPointer = stack;

uint8_t constPool[CONST_POOL_SIZE];
uint8_t constIndex;

OPCODE byteCode[CODE_ARRAY_SIZE];

#endif