%{
	#include "y.tab.h"
%}
%%
#.* {;} 
[0-9]+[0-9A-Za-z_]+ {;}
[\+|\-|\*|\/|\%] {printf("Operator: %s\n",yytext); return OP;}
[0-9]* {printf("Digit: %s\n",yytext); return DIGIT;}
int|char|bool|void|for|do|while|if|else|return {printf("Keyword: %s\n",yytext); return KEY;} 
[a-z|A-Z|_]{1}[0-9|A-Z|a-z|_]* {printf("Identifier: %s\n",yytext); return ID;}
[\(\)\;\ \{\}\=]
%%

