#include<stdio.h>
#include<stdlib.h>

int binarysearch(int arr[], int sz, int key);

int main(int argc,char *argv[],char *envp[])
{
	int searchkey,ans;
	int i, a[30];
	int n = atoi(argv[1]); // size of array

	for(i=0;i<n;i++)
	{
		a[i]=atoi(argv[i+2]);	// Get each array element from command line into a
	}
	printf("Enter the number you want to search\n");
	scanf("%d",&searchkey);
	
	ans=binarysearch(a,n,searchkey);
	
	if(ans!=-1)
		printf("Element searched is present at %d index \n", ans);
	else
		printf("Element not found!");
	return 0;
}

int binarysearch(int arr[], int sz, int key)
{
	int low, high, mid;
	low = 0;
	high = sz;
	
	while(low<=high)	
	{
		mid = (low+high)/2;
		if(arr[mid] == key)
			return mid;
		else
			if(key<arr[mid])
			   high = mid-1;
			else
			   low = mid+1;
	}
	return -1;
}
