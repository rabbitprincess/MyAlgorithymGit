#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
int main() {
	int m;
	int n;
	int r;
	int i, j, k = 0, l;
	scanf("%i %i %i", &m, &n, &r);
	int matrix[m][n];
	for (int matrix_i = 0; matrix_i < m; matrix_i++) {
		for (int matrix_j = 0; matrix_j < n; matrix_j++) {
			scanf("%i", &matrix[matrix_i][matrix_j]);
		}
	}
	//    r%=(m-1)*2+(n-1)*2;
	//my code
	int min;
	if (m>n) min = n;
	else min = m;
	min /= 2;
	for (l = 0; l<r; l++) {
		for (k = 0; k<min; k++) {
			int tmp = matrix[k][k];//좌 상단 요소 저장
			for (i = k + 1; i<n - k; i++) {
				matrix[k][i - 1] = matrix[k][i];
			}//왼으로 감(첫 요소가 tmp로 저장됨)
			for (i = k + 1; i < m - k; i++) {
				matrix[i - 1][n - k - 1] = matrix[i][n - k - 1];
			}//위로 감
			for (i = n - k - 1; i>k; i--) {
				matrix[m - k - 1][i] = matrix[m - k - 1][i - 1];
			}//오른쪽으로 감
			for (i = m - k - 1; i>k; i--) {
				matrix[i][k] = matrix[i - 1][k];
			}//아래로 감
			matrix[k + 1][k] = tmp;
		}
	}
	for (i = 0; i<m; i++) {
		for (j = 0; j<n; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
