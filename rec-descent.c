#include <stdio.h>

char ch;
int errflag = 0;

/*
	Recognition-failed message.
*/
void error()
{
	if (!errflag) {
		puts("FAIL");
		errflag = 1;
	}
}

void pa()
{
	if (ch == 'a')
		ch = getchar();
	else error();
}

void pb()
{
	if (ch == 'b')
		ch = getchar();
	else error();
}

void pc()
{
	if (ch == 'c')
		ch = getchar();
	else error();
}

/*
	0. S -> aSc
	1. S -> bA
*/
void pS()
{
	void pA();

	if (ch == 'a') {
		pa(); pS(); pc();
	}
	if (ch == 'b') {
		pb(); pA();
	}
}

/*
	2. A -> aA
	3. A -> b
	4. A -> epsilon
*/
void pA()
{
	switch (ch) {
	case 'a':
		pa(); pA();
		break;
	case 'b':
		pb();
		break;
	}
}

/*
	0. S -> aSc
	1. S -> bA
	2. A -> aA
	3. A -> b
	4. A -> epsilon
*/
int main()
{
	puts("CFG rules:");
	puts("\t1. S -> aSc");
	puts("\t2. S -> bA");
	puts("\t3. A -> aA");
	puts("\t4. A -> b");
	puts("\t5. A -> epsilon");

	//printf("Input(abb, aaaabb) = ");

	ch = getchar();
	pS();
	if (!errflag && ch == '\n') puts("OK");
	else error();

	return 0;
}
