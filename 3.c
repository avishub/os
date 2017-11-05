#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct mat
{
	int row,col,rowcol;
	int **m1, **m2, **m3;
}mat;

void accept(int **a,int row,int col);
void display(int **a,int row,int col);
int **mallocate(int row,int col);
void* mult(void*);

int main()
{
	int **a,**b, **c, i, j;
	int row1,row2,col1,col2;
	mat *m;
	pthread_t *tids;
	int count = 0, errorc;

	printf("Enter the rows and columns for matrix 1\n");
	scanf("%d%d",&row1,&col1);
	a=mallocate(row1,col1);
	accept(a,row1,col1);

	printf("Enter the rows and columns for matrix 2\n");
	scanf("%d%d",&row2,&col2);
	
	while(col1 != row2)
	{
	  printf("\nMultiplication not possible.");
	  printf("\nEnter the rows and columns for matrix 2\n");
	  scanf("%d%d",&row2,&col2);
	} 
	
	b=mallocate(row2,col2);
	accept(b,row2,col2);

	c = mallocate(row1,col2);

	printf("Matrix 1 is:\n");
	display(a,row1,col1);
	printf("\n");
	printf("Matrix 2 is:\n");
	display(b,row2,col2);
	
	
	tids = (pthread_t *)malloc(sizeof(int)*row1*col2);
	m = (mat*)malloc(sizeof(mat)*row1*col2);

	for(i=0; i<row1; i++)
	{
	  for(j=0; j<col2; j++)
	  {
	  	m[count].m1 = a;
		m[count].m2 = b;
		m[count].m3 = c;
	
		m[count].row = i;
		m[count].col = j;
		m[count].rowcol = row2; // col1	

 		errorc = pthread_create(&tids[count], NULL,(void*)&mult,(void*)&m[count]);	
 		
 		if(errorc)	
 		{
 		  printf("\nError code: %d", errorc);
 		  pthread_exit(NULL);
 		}
 		
		pthread_join(tids[count],NULL);     
		count++;
	  }
	}
	printf("\nMultiplication:\n");
	display(c,row1,col2);

	return 0;
}
int** mallocate(int row,int col)
{
	int **a;
	int i;
	a=(int**)malloc(sizeof(int*)*row);
	for(i=0;i<row;i++)
	{
		a[i]=(int*)malloc(sizeof(int)*col);
	}
	return a;
}
void accept(int **a,int row,int col)
{
	int i,j;
	printf("Enter the elements\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
}
void display(int **a,int row,int col)
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%d\t",a[i][j]);			
		}
		printf("\n");
	}
}

void* mult(void* arg)
{	
	mat *t;
	t = (mat*)malloc(sizeof(mat));
	t = (mat*)arg;
	
	int i = t->row;
	int j = t->col;
	int k;
	
	t->m3[i][j]=0;

	for (k=0;k<t->rowcol;k++)
	{
		t->m3[i][j]+=t->m1[i][k]*t->m2[k][j];
	}
	
	return NULL;
}
