#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

int main()
{
	FILE *fp;
	int fd1[2], fd2[2];
	int i, ret1, ret2;
	char ch1, ch2;
	char str1[100], str2[100], str3[100], buff1, buff2[10];
	pid_t pid;
	
	ret1 = pipe(fd1);
	ret2 = pipe(fd2);
	
	if(ret1==-1 || ret2==-1)	
	{
	  printf("\nError in creating pipe");
	}
	
	pid = fork();
	
	if(pid == 0)
	{
		//child 

		close(fd1[1]);
		close(fd2[0]);
		
		read(fd1[0],str2,100);
		
		fp = fopen(str2, "r");

		while(!feof(fp))
		{
		  ch2 = fgetc(fp);
		  write(fd2[1],&ch2, 1);
		}
		close(fd1[0]);	
		close(fd2[1]);			
	}
	else
	{
		//parent

		printf("Enter a filename: ");
		scanf("%s", str1);
		
		close(fd1[0]);
		write(fd1[1],str1,strlen(str1)+1);
		close(fd1[1]);
		

		close(fd2[1]);
		while((read(fd2[0], &ch1, 1))>0)
			printf("%c", ch1);
		close(fd2[0]);		
	}
	
	return 0; 
}
