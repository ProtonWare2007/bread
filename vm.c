#include <stdio.h>
#include "vm.h"

int16_t stack[STACK_SIZE];
int16_t* stackPointer = stack;

int16_t constPool[CONST_POOL_SIZE];
uint8_t constIndex;

OPCODE byteCode[CODE_ARRAY_SIZE];

inline static void push(int16_t word)
{
	*stackPointer = word;
	++stackPointer;
}

inline static int16_t pop()
{
	return *--stackPointer;
}

static void divide()
{
	int16_t num2 = pop();
	int16_t num1 = pop();
	push(num1 / num2);
}

static void substruct()
{
	int16_t num2 = pop();
	int16_t num1 = pop();
	push(num1 - num2);
}

static void power()
{
	int16_t num2 = pop();
	int16_t num1 = pop();
	int16_t number = 1;
	for(int16_t t = 0;t < num2;t++)
		number *= num1;
	push(number);
}

void execute()
{
	for(uint8_t i = 0;i <= 255 && byteCode[i] != RET;i++)
	{
		switch(byteCode[i])
		{
			case PUSHB:
				push(constPool[i]);
				break;
			case POPB:
				pop();
				break;
			case ADD:
				push(pop() + pop());
				break;
			case SUBS:
				substruct();
				break;
			case NEG:
				push(-pop());
				break;
			case MUL:
				push(pop() * pop());
				break;
			case DIV:
				divide();
				break;
			case POW:
				power();
				break;
			case OUT:
				printf("%d\n", (int16_t)stack[0]);
				break;
			default:
				return;
		}
	}	
}

