%{
	#include <stdio.h>
	#include <stdlib.h>
%}
%token A B
%%
ans: T B
T: A T | A {;}
%%
main() {
	printf("Enter exp: ");
	yyparse();
	printf("Valid exp\n");
}
int yyerror() {
	printf("invalid\n");
	exit(0);
}
