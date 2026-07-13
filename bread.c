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

typedef enum
{
	ADD_PREC=1,
	SUBS_PREC=1,
	MUL_PREC=2,
	DIV_PREC=2,
	LPAREN_PREC=3,
	RPAREN_PREC=0
} PRECEDENCE;

const char* source = "(-5*+(-2+4))*-8/3+1";
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

char peek()
{
	if (isAtEnd()) return '\0';
	return source[sourceIndex]; 
}

uint8_t chToInt(char ch)
{
	return (uint8_t)ch - 48;
}

bool isNumber(char ch)
{
	return ch <= 57 && ch >= 48 ? true : false;
}

void emitConst(uint8_t l)
{
	byteCode[constIndex] = PUSHB;
	constPool[constIndex++] = l;
}

void emitInfixOperation(char op)
{
	switch(op)
	{
		case '+':
			byteCode[constIndex++] = ADD;
			break;
		case '-':
			byteCode[constIndex++] = SUBS;
			break;
		case '*':
			byteCode[constIndex++] = MUL;
			break;
		case '/':
			byteCode[constIndex++] = DIV;
			break;
		default:
	}
}

void emitPrefixOperation(char op)
{
	switch(op)
	{
		case '-':
			byteCode[constIndex++] = NEG;
			break;
		case '+':
			break;
		default:
	}
}

PRECEDENCE precof(char ch)
{
	switch(ch)
	{
		case '+':
			return ADD_PREC;
		case '-':
			return SUBS_PREC;
		case '*':
			return MUL_PREC;
		case '/':
			return DIV_PREC;
		case '(':
			return LPAREN_PREC;
		case ')':
			return RPAREN_PREC;
	}
}

void expression(const char*, PRECEDENCE);

void prefix(const char* source)
{
	char l = advance();
	if(isNumber(l)) 
	{
		emitConst(chToInt(l));
	}
	else if(l == '(') 
	{
		expression(source, ADD_PREC);
	}
	else
	{
		prefix(source);
		emitPrefixOperation(l);
	}
}

void expression(const char* source, PRECEDENCE prev_prec)
{
	prefix(source);
	PRECEDENCE prec;
	while(!isAtEnd())
	{
		prec = precof(peek());
		if(prec < prev_prec) 
		{
			if(prec == 0) advance();
			return;
		}
		char op = advance();
		expression(source, prec);
		emitInfixOperation(op);
	}
}

void compile(const char* source)
{
	expression(source, ADD_PREC);
}

void debug()
{
	uint8_t i = 0;
	uint8_t data;
	do{
		data = byteCode[i];
		switch(data)
		{
			case 0:
				printf("%s %d\n", "RET", constPool[i]);
				break;
			case 1:
				printf("%s %d\n", "PUSHB", constPool[i]);
				break;
			case 2:
				printf("%s %d\n", "POPB", constPool[i]);
				break;
			case 3:
				printf("%s %d\n", "ADD", constPool[i]);
				break;
			case 4:
				printf("%s %d\n", "SUBS", constPool[i]);
				break;
			case 5:
				printf("%s %d\n", "NEG", constPool[i]);
				break;
			case 6:
				printf("%s %d\n", "MUL", constPool[i]);
				break;
			case 7:
				printf("%s %d\n", "DIV", constPool[i]);
				break;
		}
		++i;
	}while(data != 0);
	printf("%d\n", (int8_t)stack[0]);
}

int main()
{
	compile(source);
	execute();
	debug();
	return 0;
}

