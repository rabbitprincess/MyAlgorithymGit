#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int main() {
	int i, x, y, n, *a, *rank, tmp = 1;
	scanf("%d", &x);
	a = (int*)malloc(sizeof(int)*x);
	rank = (int*)malloc(sizeof(int)*x);
	for (i = 0; i < x; i++) {
		scanf("%d", &a[i]);
		if (i > 0 && a[i] < a[i - 1]) tmp++;
		rank[i] = tmp;
	}
	scanf("%d", &y);
	tmp++;
	x--;
	for (i = 0; i < y; i++) {
		scanf("%d", &n);
		while (n >= a[x] && x >= 0) {
			x--;
			if (a[x] != a[x + 1]) tmp--;
		}
		printf("%d\n", tmp);
	}
	scanf("%d", &i);
	return 0;
}