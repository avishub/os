#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<semaphore.h>
#include<math.h>

pthread_mutex_t mutex;

sem_t full;
sem_t empty;

int i=0;
int buff[5];

void * producer(void *t) 
{
	int tid = *(int *)t;
	while(1) 
	{
		int r = rand()%100;

		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		i++;
		buff[i] = r;
		printf("\nProducer %d has placed element %d in buffer", tid, r);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		
		sleep(1);
	}
	pthread_exit(NULL);
}

void * consumer(void *t) 
{
	int tid = *(int *)t;
	while(1) 
	{
		int r;

		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		r = buff[i];
		i--;
		printf("\nConsumer %d removed element %d form buffer\n", tid, r);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);

		sleep(1);
	}
	pthread_exit(NULL);
}

void main() 
{
	int prodid[10], consid[10], i;
	pthread_t prot[10], cont[10];

	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 5);
	
	pthread_mutex_init(&mutex, NULL);

	for(i=0;i<10;i++) 
	{
		prodid[i] = i;
		pthread_create(&prot[i], NULL, producer, &prodid[i]);
		sleep(1);
		consid[i] = i;
		pthread_create(&cont[i], NULL, consumer, &consid[i]);
	}

/*	for(i=0;i<10;i++) 
	{
		pthread_join(prot[i], NULL);
		pthread_join(cont[i], NULL);
	}*/

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&mutex);

}
