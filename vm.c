#include "vm.h"

static void push(uint8_t byte)
{
	*stackPointer = byte;
	++stackPointer;
}

static uint8_t pop() 
{
	return *--stackPointer;
}

static void divide()
{
	uint8_t num2 = pop();
	uint8_t num1 = pop();
	push(num1 / num2);
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
				push(-pop() + pop());
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

