#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/stat.h>

#define SZ 4096

#define DATA_NOT_FILLED_BY_SERVER -1
#define DATA_FILLED_BY_SERVER 0
#define DATA_TAKEN_BY_CLIENT 1

typedef struct buffer
{
	int status;
	int data[3];
}buffer;

int main()
{
  int shm_id, i;
  key_t mykey;
  buffer *shm_ptr;
  int data, ret_val;
  
  mykey = ftok(".", 'A');
  
  shm_id = shmget(mykey, SZ, IPC_CREAT|0666);
  if(shm_id <0)
  {
    printf("shmget error\n");
    _exit(-1);
  }
  else
  {
    printf("\nShared memory is created");
    printf("\nCreated shared memory id=%d\n",shm_id);
    
    shm_ptr = (buffer*)shmat(shm_id, NULL, 0);
    if((int)shm_ptr ==-1)
    {
      printf("\nError in shmat()");
      _exit(-1);
    }
    
    shm_ptr->status= DATA_NOT_FILLED_BY_SERVER;    
    printf("\nEnter 3 elements to write:\n");
	for(i=0; i<3; i++)
    	scanf("%d", &shm_ptr->data[i]);
    
    shm_ptr->status = DATA_FILLED_BY_SERVER;    
	
	while(shm_ptr->status != DATA_TAKEN_BY_CLIENT)
	{
	  sleep(1);
	  printf("\nServer wating for client acknowledgement");
	}
	printf("\nClient retrieved data!");
	
  }
  
  ret_val = shmdt((void*)shm_ptr);
  
  if(ret_val == 0)
  {
    printf("\nShared memory is successfully detached\n");
  }
  else
  {
  	printf("\nshmdt error\n");
  }
  return 0;
}
