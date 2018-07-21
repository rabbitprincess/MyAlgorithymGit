#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int a[100];

void Swap(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int mergeSort(int low,int high) {
	int mid = (low + high) / 2;
	if (high - low > 1) {
		mergeSort(low, mid);
		mergeSort(mid+1, high);
	}
	if (low == high) return;
	int left = low;
	int right = mid + 1;
	int i;
	int *tmpArr = (int*)malloc(sizeof(int)*(high - low + 1));



	free(tmpArr);
}

int quickSort() {


}

int main(){
	int i,j, tmp;
	
	srand((unsigned int)time(NULL));
	for(i=0;i<100;i++)
	{
		a[i] = rand()%1000;
	}
	for (i = 1; i < 100; i++) 
	{
		for (j = 1; j < 100 - i+1; j++) 
		{
			if (a[j - 1] > a[j]) 
			{
				tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
			}
		}
	}
	for (i = 0; i < 100; i++) {
		printf("%d ", a[i]);
	}//bubble sort
	printf("\n\n\n");
	for (i = 0; i<100; i++)
	{
		a[i] = rand() % 1000;
	}

	for (i = 1; i < 100; i++) 
	{
		if (a[i - 1] <= a[i]) continue;
		int tmp = a[i];
		j = i;
		while (j > 0 && a[j-1] > tmp) {
			a[j] = a[j-1];
			j--;
		}
		a[j] = tmp;
	}

	for (i = 0; i < 100; i++) {
		printf("%d ", a[i]);
	}//insert sort

	printf("\n\n\n");
	for (i = 0; i<100; i++)
	{
		a[i] = rand() % 1000;
	}
	mergeSort(0, 99);

	for (i = 0; i < 100; i++) {
		printf("%d ", a[i]);
	}//merge sort

	printf("\n");
	scanf("%d ", &i);
	return 0;
}