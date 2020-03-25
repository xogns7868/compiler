#include <stdio.h>
#include <string.h>

#define NONTERMINALS 3
#define TERMINALS 4
#define RULESIZE 6
#define MAX 100
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
	1. S -> aA
	2. S -> bB
	3. A -> aA
	4. A -> c
	5. B -> bB
	6. B -> d

	문자를 인덱스로 표시하기 위하여 아래와 같이 차례대로 A, B..nonterminal 이름 변경.

	0. A -> aB
	1. A -> bC
	2. B -> aB
	3. B -> c
	4. C -> bC
	5. C -> d
	
*/
void load_create_rule()
{
	strcpy(create_rule[0], "aB");
	strcpy(create_rule[1], "bC");
	strcpy(create_rule[2], "aB");
	strcpy(create_rule[3], "c");
	strcpy(create_rule[4], "bC");
	strcpy(create_rule[5], "d");
	puts("CFG rules:");
	puts("\t0. A -> aB");
	puts("\t1. A -> bC");
	puts("\t2. B -> aB");
	puts("\t3. B -> c");
	puts("\t4. C -> bC");
	puts("\t5. C -> d");
}

/*
	   Vn/Vt |	a	b	c	d	$
	   --------------------------------------
	     A	 |	0	1	
	     B	 |	2		3
		 C	 |		4		5
	생성 규칙이 없는 빈칸은 -1 로 표시.

	1. S -> aSb
	2. S -> bA
	3. A -> aA
	4. A -> b
*/
void load_parsing_table()
{
	parsing_table[0][0] = 0;
	parsing_table[0][1] = 1;
	parsing_table[1][0] = 2;
	parsing_table[1][2] = 3;
	parsing_table[2][1] = 4;
	parsing_table[2][3] = 5;
}

char stack_top()
{
	return stack[top - 1];
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
	top = 0;
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
			}
			else {
				printf("[error] -- Stack is not empty!\n");
				return;
			}
		}
		else { // expand -- nonterminal
			index = parsing_table[stack_top() - 'A'][*p - 'a'];
			if (index != -1) {
				str_p = rule[index];
				len = strlen(str_p);
				printf("[CFG %d] %c -> %s\n", index + 1, stack_top(), str_p);
				pop();
				for (i = len - 1; i >= 0; i--) {
					push(str_p[i]);
				}
			}
			else { // error
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
