#include<stdio.h>
#include<stdlib.h>

void PrintMatr(int** a, int n, int m) {
	if (a == NULL)
		printf("No matrix");
	else {
		printf("\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}
	}
}

int** MultMatr(int** matr1, int n1, int m1, int** matr2, int n2, int m2) {
	if (m1 != n2)
		return NULL;
	else {
		int** matr = (int**)malloc(n1 * sizeof(int));
		for (int i = 0; i < n1; i++) {
			matr[i] = (int*)malloc(m2 * sizeof(int));
			for (int j = 0; j < m2; j++) {
				matr[i][j] = 0;
				for (int k = 0; k < m1; k++)
					matr[i][j] += matr1[i][k] * matr2[k][j];
			}
		}
		return matr;
	}
}