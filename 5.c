#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

void* writer(void*);
void* reader(void*);

pthread_mutex_t x, wsem;
int readcount = 0;
char filename[] = "temp.txt";

int main()
{
	pthread_t tid[10]; 
	int t[10];
	
	pthread_mutex_init(&x, NULL);
	pthread_mutex_init(&wsem, NULL);
	
	int i;
	for(i=0; i<10; i++)
	{
		t[i] = i;
		pthread_create(&tid[i], NULL, writer, &t[i]);		
		i++;
		t[i] = i;
		pthread_create(&tid[i], NULL, reader, &t[i]);
	}
		
	for(i=0; i<10; i++)
		pthread_join(tid[i], NULL);
	
	pthread_mutex_destroy(&x);
	pthread_mutex_destroy(&wsem);
	
	return 0;
}

void* writer(void* n)
{
	int thread_no = *(int*)n;
	FILE *fp;
	char ch;
	
	pthread_mutex_lock(&wsem);
			printf("\nOpening file to write\n");
			fp = fopen(filename, "w");
			printf("Enter data to the file -> ");
			scanf("%c", &ch);
			do
			{
				fputc(ch, fp);
				scanf("%c", &ch);
			}while(ch != '.');
			fputc('\0',fp);
			fclose(fp);
		//	sleep(1);			
	pthread_mutex_unlock(&wsem);
	
	pthread_exit(NULL);
}

void* reader(void* n)
{
	int thread_no = *(int*)n;
	FILE *fp;
	char ch;	
	
	pthread_mutex_lock(&x);
		readcount++;
		if(readcount == 1)
			pthread_mutex_lock(&wsem);
	pthread_mutex_unlock(&x);
				
		fp = fopen(filename, "r");
		printf("\nReader read -> ");
		while(!feof(fp)){
			ch = fgetc(fp);
			if(ch == '\0') 
				break;
			printf("%c", ch);
		}
			
		fclose(fp);
		sleep(1);
			
	pthread_mutex_lock(&x);
		readcount--;
		if(readcount == 0)
			pthread_mutex_unlock(&wsem);
	pthread_mutex_unlock(&x);
	
	pthread_exit(NULL);
}
