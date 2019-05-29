%{
	#include <stdio.h> 
	int c;
	int operate(int a, char o, int b);
%}
%token NUM OP
%%
ans:expr1{c=$$;}
expr1:NUM OP NUM {$$=operate($1,$2,$3);}
%%
int main() {
	printf("Enter exp: ");
	yyparse();
	printf("Result is %d\n",c);
}
int yyerror() {
	printf("invalid\n");
	return 1;
}
int operate(int a, char o, int b) {
	int ret;
	switch(o) { 
		case '+' : ret = a+b; break;
		case '-' : ret = a-b; break;
		case '*' : ret = a*b; break;
		case '/' : ret = a/b; break;
		case '%' : ret = a%b; break;
	}
	return ret;
}
