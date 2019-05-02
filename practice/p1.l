%{
	#include <stdio.h>
	#include <string.h>
	int space=0, line=0,word=0,chr=0;
%}
%%
[\n] {line++;}
[\ ] {space++;}
[a-z|A-Z|0-9]* {word++; chr+=strlen(yytext);}
%%
main(int argc, char** argv) {
	yyin = fopen(argv[1],"r"); 
	yylex();
	printf("Lines: %d\n Spaces: %d\nWords: %d\nCharacters: %d\n",line,space,word,chr);
}
