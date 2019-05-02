%{
	#include <stdio.h>
	int com=0;
%}
%%
\/\/.* {com++;}
\/\*([^\*\/])*\*\/ {com++;}
%%
main(int argc, char *argv[])
 { 
	yyin = fopen(argv[1],"r");
	yyout = fopen(argv[2],"w");
	yylex();
}	
