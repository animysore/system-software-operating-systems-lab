%{
	#include "y.tab.h" 
	extern yylval;
%}
%%
[0-9]* {yylval=atoi(yytext);return NUM;}
[\+|\-|\*|\/|\%] {yylval=atoi(yytext); return PLUS;}
%%

