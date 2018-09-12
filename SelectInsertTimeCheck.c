#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

int compare(void *first, void *second)
{
	if (*(int*)first > *(int*)second)
		return -1;
	else if (*(int*)first < *(int*)second)
		return 1;
	else
		return 0;
}//reverse qsort();

void swap(int i, int j, int *arr) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void selectsort(int *arr,int n) {
	int i,j,max,iMax;
	for (i = n-1; i >= 0; i--) {
		max = 0, iMax = i;
		for (j = 0; j <= i; j++) {
			if (max < arr[j]) {
				max = arr[j];
				iMax = j;
			}
		}
		swap(i, iMax, arr);
	}
}//선택 정렬

void insertsort(int *arr,int n) {
	int i, j,tmp;
	for (i = 0; i < n; i++) {
		j = i, tmp = arr[i];
		while (tmp<arr[j - 1]) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = tmp;
	}
}//삽입 정렬


double checkTime(void (*foo)(int *arr,int n),int *arr,int n) {
	LARGE_INTEGER Frequency,BeginTime,Endtime;
	int elapsed;
	double duringtime;
	QueryPerformanceFrequency(&Frequency);

	QueryPerformanceCounter(&BeginTime); //시간 측정
    //=================================//
	foo(arr,n);
	//=================================//

	QueryPerformanceCounter(&Endtime);
	elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	duringtime = (double)elapsed / (double)Frequency.QuadPart;
	return duringtime;
}

int main()
{
	int a_i;

	for(a_i=0;a_i<5;a_i++){
		int n, i, *a, *a2;
		double time[6];
		scanf("%d", &n);
		a = (int*)malloc(sizeof(int)*n);
		a2 = (int*)malloc(sizeof(int)*n);
		for (i = 0; i < n; i++) {
			a[i] = rand()%(10000);
		}
		for (i = 0; i < n; i++) {
			a2[i] = rand() % (10000);
		}
		time[0] = checkTime(selectsort, a,n);
		time[1] = checkTime(insertsort, a2,n);
		time[2] = checkTime(selectsort, a, n);
		time[3] = checkTime(insertsort, a2, n);
		qsort(a, n, sizeof(int), compare);//reverse sort
		qsort(a2, n, sizeof(int), compare);//reverse sort
		time[4] = checkTime(selectsort, a, n);
		time[5] = checkTime(insertsort, a2, n);
		printf("\t\tnot sorted   /   sorted   /   reverse sorted\nselect sort\t%fms      %fms      %fms\ninsert sort\t%fms      %fms      %fms\n\n", time[0], time[2],time[4], time[1], time[3],time[5]);
	}
	scanf("%d", &a_i);
	return 0;
}