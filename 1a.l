%{
	#include <stdio.h> 
	int id=0, op=0;
%}
%%
[0-9]+[0-9|A-Z|a-z|_]* {;}
[a-z|A-Z|_]{1}[0-9|A-Z|a-z|_]* {id++;}
[\+|\-|\*|\/|\%] {op++;}
%%
main(int argc, char** argv) {
	yylex();
	printf("Identifiers: %d\nOperators: %d\n",id,op);
}
