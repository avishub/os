#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MAX_BUF 1024

int main()
{
    	int fd,c=0;
    	int fd1;
    	char * myfifo1="myfifo1";
    	char * myfifo2="myfifo2";
    	char str;    
    	char buf1[MAX_BUF];
    	
    	printf("\nEnter the Sentence : \n");  

    	while((str=getchar())!='#')
    	       buf1[c++]=str;
    	       
		buf1[c]='\0';
		mkfifo(myfifo1,0777);		 //(for creating fifo,prmision to user 0777)
		
        fd=open(myfifo1,O_WRONLY);
		write(fd,buf1,sizeof(buf1)); //write input to buffer
		close(fd);
		
		fd1=open(myfifo2,O_RDONLY);
		read(fd1,&buf1,sizeof(buf1));       
        printf("\nThe contents of the file are as follows : %s\n ",buf1);
		close(fd1);
	    
	    unlink(myfifo2);
	    return (0);    
}
