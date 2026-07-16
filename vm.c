#include "vm.h"

int8_t stack[STACK_SIZE];
int8_t* stackPointer = stack;

int8_t constPool[CONST_POOL_SIZE];
uint8_t constIndex;

OPCODE byteCode[CODE_ARRAY_SIZE];

static void push(int8_t byte)
{
	*stackPointer = byte;
	++stackPointer;
}

static int8_t pop() 
{
	return *--stackPointer;
}

static void divide()
{
	int8_t num2 = pop();
	int8_t num1 = pop();
	push(num1 / num2);
}

static void substruct()
{
	int8_t num2 = pop();
	int8_t num1 = pop();
	push(num1 - num2);
}

void execute()
{
	for(uint8_t i = 0;i < 256 && byteCode[i] != RET;i++)
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
			default:
				return;
		}
	}	
}

