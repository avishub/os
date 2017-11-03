#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
  pid_t cpid;
  
  cpid = fork();
  if(cpid == 0)
  {
    printf("\n(child) My process id is %d ", getpid());
    printf("\n(child) My parent process is %d", getppid());
  }
  else
  {
    sleep(5);
    printf("\n(parent) My process id is %d", getpid());
    printf("\n(parent) My parent process id is %d\n", getppid());
    printf("\n(parent) My child process id is %d\n", cpid);
  }
  
  return 0;
}
