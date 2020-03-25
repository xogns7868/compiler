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

void pd()
{
	if (ch == 'd')
		ch = getchar();
	else error();
}

/*
	A -> aBc
	A -> Bc
	A -> dAa
*/
void pA()
{
	void pB();

	if (ch == 'a') {
		pa(); pB(); pc();
	}
	else if (ch == 'd') {
		pd(); pA(); pa();
	}
	else {
		pB(); pc();
	}
}

/*
	B -> bB
	B -> epsilon
*/
void pB()
{
	switch (ch) {
	case 'b':
		pb(); pB();
		break;
	case ' ':
		break;
	}
}

/*
	A -> aBc
	A -> Bc
	A -> dAa
	B -> bB
	B -> epsilon
*/
int main()
{
	puts("CFG rules:");
	puts("\t1. A -> aBc");
	puts("\t2. A -> Bc");
	puts("\t3. A -> dAa");
	puts("\t4. B -> bB");
	puts("\t5. B -> epsilon");

	//printf("Input(abb, aaaabb) = ");

	ch = getchar();	
	pA();
	if (!errflag && ch == '\n') puts("OK");
	else error();
		
	return 0;
}
