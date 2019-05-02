#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct Terminal
{
    char rule[2][10],first[10],follow[10],table[2][10];
    int ft, fot; //ft is first pointer and fot is follow pointer
} Term;
//r[0] is A and r[1] is B. stop is the top for stack and ipr is the pointer for input
Term r[2];
char *ip="abba$", stack[20];
int stop=-1,ipr = 0;

int isterminal(char c)
{
    if(islower(c) || c=='3') return 1;
    return 0;
}

void calfirst(int rno)
{
    int i,j;
    for(j=0;j<2;j++) { 
        if (rno ==0 && j==1) break;
        for(i=2;r[rno].rule[j][i]!='\0';i++)
        {   
            if(isterminal(r[rno].rule[j][i]))
            {
                r[rno].ft++;
                r[rno].first[r[rno].ft]=r[rno].rule[j][i];
                r[rno].first[r[rno].ft+1]='\0';
                break;
            }
        }
    }
}

void calfollow(int rno)
{
    int i,j,k;
    if(rno==0)
    {
        r[rno].follow[++r[rno].fot]='$';
        r[rno].follow[r[rno].fot+1]='\0';
    }
    for (k=0;k<2;k++) { 
        
        for(i=2;r[rno].rule[0][i]!='\0';i++)
        {
            if(r[rno].rule[0][i]=='A')
                j=0;
            if(r[rno].rule[0][i]=='B')
                j=1;
            if(r[rno].rule[0][i]=='A'||r[rno].rule[0][i]=='B')
            {
                if(isterminal(r[rno].rule[k][i+1]) && r[rno].rule[k][i+1]!='3')
                {
                    r[j].follow[++r[j].fot]=r[rno].rule[k][i+1];
                }
                else
                {
                    if(r[rno].rule[k][i+1]=='A')
                        strcat(r[j].follow,r[0].first);
                    if(r[rno].rule[k][i+1]=='B')
                        strcat(r[j].follow,r[1].first);                
                }  
            }
        }
    }
}

void maketable(int rno)
{
    int i,j;
    for(i=0;r[rno].first[i]!='\0';i++)
    {
        switch(r[rno].first[i])
        {
            case 'b': j=1; break;
            case 'a':
            case '3': j=0;
        }
        if(r[rno].first[i]=='3')
        {
            strcpy(r[rno].table[j],r[rno].rule[1]);
        }
        else
            strcpy(r[rno].table[j],r[rno].rule[0]);
    }
}

void stackcall()
{
    int k;
    while(!(stack[stop]=='$' && ip[ipr]=='$'))
    {
        printf("Stack: ");
        for(k=stop;k>=0;k--)    printf("%c",stack[k]);

        printf("\tinput %s\t",ip+ipr);
        if(ip[ipr]=='a' && stack[stop]=='A')
        {
            printf("prod: %s\n",r[0].rule[0]);
            stop--;
            stack[++stop]='a';stack[++stop]='B';stack[++stop]='a';
        }
        else if(stack[stop]=='B' && ip[ipr]=='b')
        {
            printf("prod: %s\n",r[1].rule[0]);
            stop--;
            stack[++stop]='B';stack[++stop]='b';
        }
        else if(stack[stop]=='B' && ip[ipr]=='a')
        {
            printf("prod: %s\n",r[1].rule[1]);
            stop--;
        }
        if((stack[stop]==ip[ipr])&&stack[stop]!='$')
        {
            stop--;
            ipr++;
        }
    }
    printf("Stack: $\tinput: $\tprod: \n");
    printf("String accepted.\n");
}

void main()
{
    strcpy(r[0].rule[0],"A=aBa");
    strcpy(r[1].rule[0],"B=bB");
    strcpy(r[1].rule[1],"B=3");
    strcpy(r[0].rule[1],"");
    r[0].fot=r[0].ft=r[1].fot=r[1].ft=-1;
    int i;
    for(i=0;i<2;i++)
    {
        calfirst(i);
    }
    printf("First of A %s \n",r[0].first);
    printf("First of B %s \n",r[1].first);
    for(i=0;i<2;i++)
    {
        calfollow(i);
    }
    printf("Follow of A %s \n",r[0].follow);
    printf("Folow of B %s \n",r[1].follow);
    for(i=0;i<2;i++)
    {
        maketable(i);
    }
    printf("M[A,a]= %s\n",r[0].table[0]);
    printf("M[B,a]= %s\n",r[1].table[0]);
    printf("M[B,b]= %s\n",r[1].table[1]);
    stack[++stop]='$';
    stack[++stop]='A';
    stackcall();
}