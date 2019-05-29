%{
	#include <stdio.h>
	#include <stdlib.h>
	int c = 0, n;
%}
%token A B NUM NL
%%
ans: NUM NL T B NL {n=$1;}
T: A T {c++;}
| A {c++;}
%%
main() {
	printf("Enter Num followed by Exp: ");
	yyparse();
	if(c==n)
		printf("Valid exp\n");
	else
		printf("Invalid exp\n");
}
int yyerror() {
	printf("invalid\n");
	exit(0);
}
