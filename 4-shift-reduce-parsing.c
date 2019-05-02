#include <stdio.h>
#include <string.h>

char *rules[] = {
                    "E+T",
                    "T*F", 
                    "T",
                    "F",
                    "(E)",
                    "i"
                };
char head[6]= {'E','T','E','T','F','F'};
char action[10],a[10]="i+i*i$",stack[10]="$";
int top=0,ipr=0;

char* strstr1(char* stack, char* rule)
{
    int lenofstack = strlen(stack);
    for(int start=strlen(stack)-strlen(rule),i=0;start<=lenofstack;start++,i++)
    {
        if(stack[start]!=rule[i])
            return '\0';
    }
    return rule;
}

int canbereduced()
{
    if(top==0)
        return 0;
    char *p;
    for(int i=0;i<6;i++)
    {
        p=strstr1(stack,rules[i]);
        if(p)
        {
            if((i==0 && a[ipr]!='$')||(i==2&&a[ipr]=='*'&&stack[top]=='T'))
                return 0;
            else
            {
                top-=strlen(rules[i]);
                stack[++top]=head[i];
                stack[top+1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    printf("STACK\tI/P\tACTION\n");
    char temp[20];
    while(1)
    {
        strcpy(temp,"");
        strncpy(temp,stack,top);
        printf("%s\t%s\t",stack,a+ipr);
        if(stack[top]=='E'&&stack[top-1]=='$'&&a[ipr]=='$')
        {
            printf("Accept\n");
            return 1;
        }
        if(canbereduced())
        {
            printf("Reduce\n");
        }
        else 
        {
            if(a[ipr]!='$')
            {
                stack[++top]=a[ipr++];
                stack[top+1]='\0';
            }
            else
            {
                printf("ERROR\n");
                return 0;
            }
            printf("Shift\n");
        }
    }
}