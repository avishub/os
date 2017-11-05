
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MAX_BUF 1024

int main()
{
		int fd,fd1;
		
    	char *myfifo1="myfifo1";
    	char * myfifo2="myfifo2";
    	char buf[MAX_BUF];     	
     	
    	int words=0,len=0,i=0,lines=0,chars=0;
    
    	FILE *fp;

     	mkfifo(myfifo2,0777);
 
      fd=open(myfifo1,O_RDONLY);
	    read(fd,buf,MAX_BUF);
	    printf("Content of pipe:\n");
	    printf("%s",buf);
	    
	    while(buf[i]!= '\0')
	    {

	     	  if(buf[i]==' '|| buf[i]=='\n')
		  words++;
			else
		 	 chars++;
		
			if(buf[i]=='\n')
		     lines++;
		     i++;
	    }
	    
	    printf("\nNo. of Words : %d",words);
	    printf("\nNo. of Lines : %d",lines);
	    printf("\nNo. of Chars : %d",chars);	
	      
	    fp=fopen("test.txt","w+");
	    fprintf(fp,"\n No. of Words : %d",words);
	    fprintf(fp,"\n No. of Lines : %d",lines);
	    fprintf(fp,"\n No. of Chars : %d",chars);
		
	    fclose(fp);
	    close(fd);
	    unlink(myfifo1);

	    fd=open("test.txt",O_RDONLY);	 
	    fd1=open(myfifo2,O_RDWR);
	    read(fd,&buf,sizeof(buf)); 
	    write(fd1,buf,sizeof(buf));  	    
        //system("cat test.txt > myfifo2");		  
	    close(fd1);
	    close(fd);
	    return 0;
}
