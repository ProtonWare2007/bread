#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vm.h"

/*

expr = (expr(+ | -))* factor
factor = (factor(* | /))* atom
atom = prefix | '('expr')'
prefix = (-prefix)* | NUMBER

//NUMBER ()  * /  + -
//infix_op: +|-|*|/ : left associative
//prefix_op: - : right associative
*/

const char* source = "5+3";
uint8_t sourceIndex;

bool isAtEnd()
{
	return source[sourceIndex] == '\0' ? true : false;
}

char advance()
{
	if (isAtEnd()) return '\0';
	return source[sourceIndex++]; 
}

uint8_t chToInt(char ch)
{
	if(ch <= 57 && ch >= 48)
		return (uint8_t)ch - 48;
	return 10;
}

void emitConst(uint8_t l)
{
	constPool[constIndex++] = l;
}

void expression(const char* source)
{
	uint8_t l =  chToInt(advance());
	emitConst(l);
	printf("%d\n", constPool[0]);
}

void compile(const char* source)
{
	expression(source);
}

int main()
{
	compile(source);
	return 0;
}

