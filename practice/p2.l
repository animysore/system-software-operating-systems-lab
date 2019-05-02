%{
	#include <stdio.h> 
	int pf=0, sf=0;	
%}
%%
"printf" {pf++; fprintf(yyout,"write");}
"scanf" {sf++; fprintf(yyout,"read");}
%%
main(int argc, char** argv) {
	yyin = fopen(argv[1],"r");
	yyout = fopen(argv[2],"w"); 
	yylex();
	printf("Pf: %d\n Sf: %d\n",pf,sf);
}
