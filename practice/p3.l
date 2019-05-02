%{
	#include <stdio.h> 
	int cs=0, ss=0;	
%}
%%
(\ )?([a-z|A-Z]*\ )*["and"|"or"|"but"](\ [a-z|A-Z]*)+\. {cs++; printf("\nCS : "); ECHO;}
(\ )?([a-z|A-Z]*\ *)*\. {ss++; printf("\nSS : "); ECHO;}
%%
main(int argc, char** argv) {
	yyin = fopen(argv[1],"r");
	yylex();
	printf("CS: %d\n SS: %d\n",cs,ss);
}
