#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Swap(int *arr, int x, int y) {
	int tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

int partition(int *arr, int left, int right) {
	int x1 = rand() % (right - left + 1) + left, x2 = rand() % (right - left + 1) + left, x3 = rand() % (right - left + 1) + left, pivot;
	if (left + 2 > right) pivot = x1;//원소 두개 이하일때 까지는 왼쪽거가 pivot
	else {
		if ((arr[x1] >= arr[x2] && arr[x3] >= arr[x1]) || (arr[x1] <= arr[x2] && arr[x3] <= arr[x1])) pivot = x1;
		else if ((arr[x2] >= arr[x1] && arr[x3] >= arr[x2]) || (arr[x2] <= arr[x1] && arr[x3] <= arr[x2])) pivot = x2;//x1이 젤큼
		else pivot = x3;
	}//pivot 중간값 찾기 방법. pivot값은 left에 존재.
	Swap(arr, left, pivot);//왼쪽 원소로 hide*/
	int low = left + 1, high = right;
	while (low <= high) {
		while (arr[left] >= arr[low] && low <= high) low++;
		while (arr[left] <= arr[high] && high >= low) high--;//중복값 찾기 가능
		if (low <= high) Swap(arr, low, high);
	}
	Swap(arr, left, high);
	return high;
}

void QuickSort(int *arr, int l, int r) {
	if (l <= r) {
		int pivot = partition(arr, l, r);
		QuickSort(arr, l, pivot - 1);
		QuickSort(arr, pivot + 1, r);
	}
}

int binarySearch(int *arr, int left, int right, int k) {
	while (left <= right)
	{
		int pivot = (right + left) / 2;
		if (arr[pivot] == k) return pivot;
		else if (arr[pivot] < k) left = pivot + 1;
		else right = pivot - 1;
	}
	return left;
}

int main() {
	int i, n, *arr, x, result;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) scanf("%d", &arr[i]);
	QuickSort(arr, 0, n - 1);
	for (i = 0; i < n; i++) printf(" %d", arr[i]);
	printf("\n");
	scanf("%d", &x);
	result = binarySearch(arr, 0, n - 1, x);
	if (arr[result] == x) printf("값 %d이 %d번째 인덱스에 존재합니다.", x, result + 1);
	else {
		printf("값 %d는 존재하지 않습니다.\n", x);
		if (result == 0) printf("%d번째 인덱스 값 %d 앞에 들어갑니다.", result, arr[result]);
		else if (result == n) printf("%d번째 인덱스 값 %d 뒤에 들어갑니다", result - 1, arr[result - 1]);
		else printf("%d번째 인덱스 값 %d와 %d번째 인덱스 값 %d 사이에 들어갑니다.", result - 1, arr[result - 1], result, arr[result]);
	}
	free(arr);
	scanf("%d", &x);
	return 0;
}