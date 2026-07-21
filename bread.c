#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "vm.h"
#include "compiler.h"

#define error(msg) fprintf(stderr, "%s\n", msg)
void debug();
void readFile(const char*);

enum ERRORS
{
	EX_USAGE=64,
	MEM_ALLOC=10
};

int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		readFile(argv[1]);
		compile();
		execute();
		debug();
	} else
	{
		error("error: input file is required!");
		error("Usage: <file>");
		return EX_USAGE;
	}
	return 0;
}

void allocate_source(long fsize)
{
	source = (char*)malloc(sizeof(char) * (fsize + 1));
	if(source  == NULL)
	{
		error("unable to allocate memory for the input program");
		exit(MEM_ALLOC);
	}
}

void readFile(const char* path)
{
	FILE* filep = fopen(path, "r");
	if(filep == NULL)
	{
		fclose(filep);
		error("failed to open input file");
		exit(errno);
	}
	fseek(filep, 0, SEEK_END);
	long fsize = ftell(filep);
	rewind(filep);
	allocate_source(fsize);
	fread(source, sizeof(char), fsize, filep);
	*(source + fsize) = '\0';
	fclose(filep);
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
			case 8:
				printf("%s %d\n", "POW", constPool[i]);
				break;
		}
		++i;
	}while(data != 0);
	printf("%d\n", (int16_t)stack[0]);
}
