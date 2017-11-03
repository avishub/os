#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<wait.h>

void asc(int *a,int sz);

int main()
{
	int a[30],n,i,status,j;
	char *str[100], *ch;
	pid_t pid, cpid ;

	printf("Enter the size of array \n");
	scanf("%d",&n);
	printf("Enter %d elements\n", n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	
	asc(&a, n);			
	/*printf("Array in sorted order: ")  ;
    for(i=0; i<n; i++)
    {
      printf("%d\t",a[i] );
    }*/
	pid = fork();
	
	switch(pid)
	{
	case -1:
		printf("Error in fork()\n");
		break;
	case 0:			
		str[0]="bs";
		asprintf(&ch,"%d",n);
		str[1]=ch;

		for(i=0;i<n+2;i++)
		{
			asprintf(&ch,"%d",a[i]);
			str[i+2]=ch;
		}	
		str[i+2] = NULL;		
		
		execve("bs",str,NULL);
		break;
	default:		 
		wait(&status);
	}
	return 0;
}

void asc(int *a,int sz)
{
   int i, j;
   int temp;
  
   for(i=0; i<sz; i++) 
   {
    for(j=i+1; j<sz; j++)
    {
        if(a[i]>a[j])
        {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;   
        }
    }
   } 
}
