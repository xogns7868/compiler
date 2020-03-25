/*
	Predictive parser
	2017.11.03 by Kang, Seung-Shik at Kookmin University
*/
#include <stdio.h>
#include <string.h>

#define NONTERMINALS 2
#define TERMINALS 5
#define RULESIZE 5
#define MAX 100

//#define INPUT_END_MARK '$'
#define STACK_BOTTOM_MARK '_'

char create_rule[RULESIZE][MAX];
int parsing_table[NONTERMINALS][TERMINALS];
char stack[999];
int top;

void input_data(char *str)
{
	scanf("%s", str);
	strcat(str, "$");
}

/*

	문자를 인덱스로 표시하기 위하여 아래와 같이 차례대로 A, B..nonterminal 이름 변경.

	1. A -> aBc
	2. A -> Bc
	3. A -> dAa
	4. B -> bB
	5. B -> epsilon
*/
void load_create_rule()
{
	strcpy(create_rule[0], "aBc");
	strcpy(create_rule[1], "Bc");
	strcpy(create_rule[2], "dAa");
	strcpy(create_rule[3], "bB");
	strcpy(create_rule[4], "");

	puts("CFG rules:");
	puts("\t1. A -> aBc");
	puts("\t2. A -> Bc");
	puts("\t3. A -> dAa");
	puts("\t4. B -> bB");
	puts("\t5. B -> epsilon");
}

/*
	   Vn/Vt |	a	b	c	d	$
	   --------------------------------------
	     A	 |	0	1	1	2
	     B	 |		3	4		4
	생성 규칙이 없는 빈칸은 -1 로 표시.

	0. A -> aBc
	1. A -> Bc
	2. A -> dAa
	3. B -> bB
	4. B -> epsilon
*/
void load_parsing_table()
{
	parsing_table[0][0] = 0;
	parsing_table[0][1] = 1;
	parsing_table[0][2] = 1;
	parsing_table[0][3] = 2;
	parsing_table[1][1] = 3;
	parsing_table[1][2] = 4;
	parsing_table[1][4] = 4;
}

char stack_top()
{
	return stack[top-1];
}

void push(char ch)
{
	stack[top++] = ch;
}

void pop()
{
	top--;
}

void init_stack()
{
	top=0;
	push(STACK_BOTTOM_MARK);
	push('A');
}

int is_nonterminal(char ch)
{
	if ('A' <= ch && ch <= 'Z') return 1;
	else return 0;
}

int is_terminal(char ch)
{
	return (is_nonterminal(ch) == 0);
}

void predictive_parsing(int table[NONTERMINALS][TERMINALS], char rule[RULESIZE][MAX], char *input)
{
	char *p = input;
	char *str_p;
	int i, index=0, len;

	while (1) {
		if (stack_top() == STACK_BOTTOM_MARK) {
			if (*p == '$')
				printf("[accept]\n");	// parsing OK
			else printf("[error] -- Input is not empty!\n");
			return;
		}

		if (is_terminal(stack_top())) {	// pop -- terminal symbol
			if (*p == stack_top()) {
				pop();
				p++;
			} else {
				printf("[error] -- Stack is not empty!\n");
				return;
			}
		} else { // expand -- nonterminal
			index = parsing_table[stack_top()-'A'][*p-'a'];
			if (index != -1) {
				str_p = rule[index];
				len = strlen(str_p);
				printf("[CFG %d] %c -> %s\n", index+1, stack_top(), str_p);
				pop();
				for (i=len-1; i>=0; i--) {
					push(str_p[i]);
				}
			} else { // error
				printf("[error] %c -> %c\n", stack_top(), *p);
				return;
			}
		}
	}
}

int main()
{
	char input[100];

	load_create_rule();
	load_parsing_table();

	input_data(input);
	init_stack();

	predictive_parsing(parsing_table, create_rule, input);
	return 0;
}
