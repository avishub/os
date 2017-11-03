#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
  pid_t cpid;
  
  cpid = fork();
  
  if(cpid == 0)
  {   
    sleep(20) ;
    printf("\n(Child) My process id is %d ", getpid());
    printf("\n(Child) My parent process is %d", getppid());
  }
  else
  {
  	sleep(5);
    printf("\n(Parent) My child process id is %d", cpid);    
    printf("\n(Parent) My process id is %d", getpid());
    printf("\n(parent) My parent process id is %d\n", getppid());
  }
  
  return 0;
}
