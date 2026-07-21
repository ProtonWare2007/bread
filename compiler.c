#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "vm.h"
#include "compiler.h"
#include "common.h"

char* source;
uint8_t sourceIndex;

static bool isAtEnd()
{
	return source[sourceIndex] == '\0' ? true : false;
}

static bool isNumber(char ch)
{
	return ch <= 57 && ch >= 48 ? true : false;
}

static bool isWhiteSpace(char ch)
{
	switch(ch)
	{
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			return true;
		default:
			return false;
	}
}

static char peek()
{
	if (isAtEnd()) return '\0';
	return source[sourceIndex];
}

static void skipWhiteSpace()
{
	while(isWhiteSpace(peek()))
	{
		++sourceIndex;
	}
}

static char advance()
{
	if (isAtEnd()) return '\0';
	return source[sourceIndex++];
}

static int16_t chToInt(char ch[])
{
	int16_t number = 0;
	for(uint8_t i = 0;ch[i] != '\0';i++)
	{
		number *= 10;
		number += (int16_t)ch[i] - 48;
	}
	return number;
}

static void emitConst(int16_t l)
{
	byteCode[constIndex] = PUSHB;
	constPool[constIndex++] = l;
}

static void emitInfixOperation(char op)
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
		case '^':
			byteCode[constIndex++] = POW;
			break;
		default:;
	}
}

static void emitPrefixOperation(char op)
{
	switch(op)
	{
		case '-':
			byteCode[constIndex++] = NEG;
			break;
		case '+':
			break;
		default:;
	}
}

static PRECEDENCE precof(char ch)
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
		case '^':
			return POW_PREC;
		case '(':
			return LPAREN_PREC;
		case ')':
			return RPAREN_PREC;
		default:
			return NONE_PREC;
	}
}

static bool right_assoc(char op)
{
	switch(op)
	{
		case '^':
			return true;
		default:
			return false;
	}
}

void prefix(const char* source)
{
	skipWhiteSpace();
	char l = advance();
	if(isNumber(l))
	{
		char str[6] = {'\0'};
		uint8_t index = 1;
		str[0] = l;
		while(isNumber(peek()))
		{
			str[index++] = advance();
		}
		emitConst(chToInt(str));
	}
	else if(l == '(')
	{
		expression(source, NONE_PREC);
	}
	else
	{
		prefix(source);
		emitPrefixOperation(l);
	}
}

static void consume(char token, const char* error_msg)
{
	if(isAtEnd() || advance() != token)
	{
		error(error_msg);
		exit(MISSING_TOKEN);
	}
}

static void expression(const char* source, PRECEDENCE prev_prec)
{
	prefix(source);
	char op;
	skipWhiteSpace();
	while(!isAtEnd() && peek() != ';')
	{
		op = peek();
		PRECEDENCE prec = precof(op);
		if(prec > prev_prec && !right_assoc(op) || right_assoc(op))
		{
			advance();
			expression(source, prec);
		} else
		{
			if(prec == RPAREN_PREC && prev_prec == 1) advance();
			return;
		}
		emitInfixOperation(op);
	}
	consume(';',"error: missing semicolon after expression statement!");
}

static void writecStatement()
{
	const char* tokens = "writec";
	for(uint8_t i = 0;i<6;i++)
		consume(*(tokens+i),"error: unknown statement!");
	if(!isWhiteSpace(peek()))
	{
		error("error: unknown statement!");
		exit(UKNOWN_STATEMENT);
	}
	expression(source, NONE_PREC);
	byteCode[constIndex++] = OUT;
}

void compile()
{
	skipWhiteSpace();
	while(!isAtEnd())
	{
		switch(peek())
		{
			case 'w':
				writecStatement();
				break;
			case 'd':
				break;
			default:
				expression(source, NONE_PREC);
		}
		skipWhiteSpace();
	}
}

