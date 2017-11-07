#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/types.h>
sem_t room;
sem_t forks[5];

void * philosopher(void *pid)
{
	int t = *(int *)pid;

	while(1) {
		printf("\nPhilosopher %d is thinking...", t);

		sem_wait(&room);
		sem_wait(&forks[t]);
		sem_wait(&forks[(t+1)%5]);
		printf("\nPhilosopher %d took forks %d and %d and started eating.\n", t, t, (t+1)%5);
		sleep(1);

		sem_post(&forks[(t+1)%5]);
		sem_post(&forks[t]);
		sem_post(&room);
		printf("\nPhilosopher %d is put down the forks...", t);
	}
	pthread_exit(NULL);
}

void main(){

	int pid[5] = {0, 1, 2, 3, 4};
	int i;
	pthread_t tid[5];

	sem_init(&room, 0, 4);

	for(i=0;i<5;i++) 
		sem_init(&forks[i], 0, 1);

	for(i=0;i<5;i++) 
		pthread_create(&tid[i], NULL, philosopher, &pid[i]);

	for (i = 0; i < 5; ++i)	
		pthread_join(tid[i], NULL);
	
	sem_destroy(&room);
	for (i = 0; i < 5; ++i)
		sem_destroy(&forks[i]);

}
