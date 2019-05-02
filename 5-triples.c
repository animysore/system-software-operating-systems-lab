#include <stdio.h>

void main()
{
    FILE *ip=fopen("ip.txt","r");
    FILE *op=fopen("op.txt","w");
    char pos,opr,arg1,arg2;
    while( fscanf(ip," %c%c%c%c",&pos,&opr,&arg1,&arg2) != EOF )
    {
        printf("OPR %c\n",opr);
        if(opr=='+')
        {
            fprintf(op,"MOV R0,%c \nADD R0,%c \nMOV T%c,R0\n",arg1,arg2,pos);
        }
        else if(opr=='*')
        {
            fprintf(op,"MOV R0,%c \nMUL R0,%c \nMOV T%c,R0\n",arg1,arg2,pos);
        }
        else if(opr=='/')
        {
            fprintf(op,"MOV R0,%c \nDIV R0,%c \nMOV T%c,R0\n",arg1,arg2,pos);
        }
        else if(opr=='-' && arg2!='@')
        {
            fprintf(op,"MOV R0,%c \nSUB R0,%c \nMOV T%c,R0\n",arg1,arg2,pos);
        }
        else if(opr=='-')
        {
            fprintf(op,"MOV R0,-%c \nMOV T%c,R0\n",arg1,pos);
        }
        else if(opr=='=')
        {
            fprintf(op,"MOV %c,%c\n",arg1,arg2);
        }
    }            
}