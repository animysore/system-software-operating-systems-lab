%{
	#include <stdio.h>
	#include <stdlib.h>
	int id =0, dig=0, op=0, key=0;
%}
%token OP DIGIT ID KEY 
%%
input: DIGIT input { dig++;}
| OP input {op++;}
| ID input {id++;}
| KEY input {key++;}
| DIGIT { dig++;}
| OP  {op++;}
| ID {id++;}
| KEY {key++;}
;
%%
extern FILE* yyin;
main(int argc, char * argv[]) {
	yyin = fopen(argv[1],"r");
	yyparse();
	printf("Operators: %d | Digits: %d | Identifiers: %d | Keywords: %d\n",op,dig,id,key);
}
int yyerror() {
	printf("invalid\n");
	exit(0);
}
