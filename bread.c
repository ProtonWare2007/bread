#include <stdio.h>
#include <stdint.h>

#define STACK_SIZE 256

uint8_t stack[STACK_SIZE];
uint8_t* stackPointer = stack;

void push(uint8_t byte)
{
	*stackPointer = byte;
	++stackPointer;
}

uint8_t pop() 
{
	return *--stackPointer;
}

int main()
{
	push(5);
	push(6);
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;
}


