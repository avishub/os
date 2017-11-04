#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>

#define sz 4096

typedef struct message
{
  int status;
  char msg[sz];
}message;

int main()
{
  int shm_id, ret_remove, running=1;
  key_t mykey;
  char buffer[sz];
  message* shm_ptr;
  
  mykey = ftok(".",'C');
  
  shm_id = shmget(mykey,sz,IPC_CREAT|0666); 
  if(shm_id < 0) 
  {
     printf("\nproducer: shmget() error");
     exit(-1);
  }
  printf("\n(producer)Shared Memory id:%d",shm_id);
  
  shm_ptr = (message*)shmat(shm_id, NULL, 0);
  if((int)shm_ptr == -1)
  {
    printf("\nproducer:shmat() error");
    exit(-1);
  }
  
  printf("\nproducer:Shared memory attached at %x address", (int)shm_ptr);
  
  while(running)
  {
    while(shm_ptr->status == 1)
    {
       sleep(1);
       printf("\nProducer: waiting for counsumer");
    }
    
    printf("\nproducer: Enter an item to be produced\n");
    gets(buffer);
    
    strcpy(shm_ptr->msg, buffer);
    shm_ptr->status=1;
    
    if(strncmp(buffer, "exit", 3) == 0)
    {
      running = 0;
    }
  }
  
  ret_remove = shmdt((void*)shm_ptr);
  if(ret_remove == -1)
  {
     printf("\nproducer: shared meemory detach error");
  }
  else
  {
       printf("\nproducer: shared meemory detached");
  }
    
  ret_remove = shmctl(shm_id, IPC_RMID, NULL);
  
  if(ret_remove == -1)
  {
     printf("\nproducer: shared meemory reomove error");
  }
  else
  {
       printf("\nproducer: shared meemory reomved");
  }
  
  return 0;
}
