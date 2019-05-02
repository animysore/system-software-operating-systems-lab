#include <stdio.h>
#include <stdlib.h>

int max[10][10],alloc[10][10],need[10][10],avail[10],finished[10]={0},newavail[10],alloctemp[10];
int nr,np;

void calneed()
{
	int i,j;
	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
			need[i][j] = max[i][j]-alloc[i][j];
	}
}

void calsafe()
{
	int flag = 0, i,j,k,zo,nzo,flag2;
	/*
	flag is used to check safe or unsafe, if flag is never changed to 1 in an iteration then no process has been allocated
	zo is used to store the zero avail process 
	nzo is used to store the non zero process
	both are set to -1, if a nzo procc exists it is given priority
	flag 2 is used to check if a proc has any zero elements or greater than zero elements
	*/
	for(i=0;i<np;i++)
	{
		zo=-1;
		nzo=-1;
		flag=0;
		for(j=0;j<np;j++)
		{	flag2=-1;
			if(finished[j]==0)
			{
				for(k=0;k<nr;k++)
				{
					if(need[j][k]==avail[k])
					{
	 					if(flag2!=2)
						flag2=0;
							
					}
					else if(need[j][k]<avail[k])
					{
						if(flag2!=0&&flag2!=2)
							flag2=1;
					}
					else
						flag2=2;
				}
				if(flag2==2)
					continue;
				if(flag2==1)
					nzo=j;
				else if(flag2==0)
					zo=j;
			}
		}
		if(nzo!=-1 || zo!=-1)
		{
			flag =1;
			if(nzo!=-1)
				j=nzo;
			else
				j=zo;
			finished[j]=1;
			for(k=0;k<nr;k++)
			{
				avail[k] = avail[k] - need[j][k] + max[j][k];
			}
			printf("%d ",j);
		}
		if(flag==0)
		{
			printf("Unsafe\n");
			exit(0);
		}
	}
	printf("\nAvail:\n");
	for(i=0;i<nr;i++)
	printf("%d ",avail[i]);
}

int main()
{
	int i,j;
	char choice='y';
	printf("Enter number of resources and processes\n");
	scanf("%d%d",&nr,&np);
	printf("Enter max\n");
	for(i=0;i<np;i++)
	{
		printf("Enter max for %d\n",i);
		for(j=0;j<nr;j++)
			scanf("%d",&max[i][j]);
	}
	printf("Enter alloc\n");
	for(i=0;i<np;i++)
	{
		printf("Enter alloc for %d\n",i);
		for(j=0;j<nr;j++)
			scanf("%d",&alloc[i][j]);
	}
	printf("Enter avail\n");
	for(i=0;i<nr;i++)
	{
		scanf("%d",&avail[i]);
		newavail[i]=avail[i];
	}
	calneed();
	printf("Processes:\n");
	calsafe();
	printf("Is there more resources to allocate? y/n\n");
	scanf(" %c",&choice);
	while(choice=='y')
	{
		int flag = 0;
		for(i=0;i<nr;i++)
		{
			avail[i]=newavail[i];
		}
		printf("Enter process name.\n");
		scanf("%d",&i);
		printf("Enter the resources:\n");
		for(j=0;j<nr;j++)
		{
			scanf("%d",&alloctemp[j]);

			alloc[i][j]+=alloctemp[j];
			if(avail[j]>=alloctemp[j])
			{
				avail[j]-=alloctemp[j];
			}
			else
			{
				printf("Cannot allocate for resource!\n");
				flag = 1;
			}
		}
		if(flag==0)
		{
			for(j=0;j<nr;j++)
			{
				newavail[j]=avail[j];
			}
			calsafe();
		}
		else
		{
			printf("Resetting allocated to previous.\n");
			for(j=0;j<nr;j++)
			{
				avail[i]=newavail[i];
				alloc[i][j]-=alloctemp[j];
			}
		}
		printf("Is there more resources to allocate? y/n\n");
		scanf(" %c",&choice);
	}
	return 0;
}