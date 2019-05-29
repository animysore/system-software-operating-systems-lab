%{
	#include "y.tab.h" 
	extern int yylval;
%}
%%
[0-9]* {yylval=atoi(yytext);return NUM;}
[\+|\-|\*|\/|\%] {yylval=yytext[0]; return OP;}
%%

