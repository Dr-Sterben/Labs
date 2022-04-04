//Произведение матриц произвольного размера
#include<stdio.h>
#include<stdlib.h>
#include"Header.h"

int main() {
	int n1 = 0, m1 = 0, n2 = 0, m2 = 0;
	printf("Enter first matrix size (N, M): ");
	scanf_s("%d %d", &n1, &m1);
	int** matr1 = (int**)malloc(n1 * sizeof(int));
	for (int i = 0; i < n1; i++) {
		matr1[i] = (int*)malloc(m1 * sizeof(int));
		for (int j = 0; j < m1; j++) {
			printf("Element [%d][%d] = ", i + 1, j + 1);
			scanf_s("%d", &matr1[i][j]);
		}
	}
	printf("Enter second matrix size (N, M): ");
	scanf_s("%d %d", &n2, &m2);
	int** matr2 = (int**)malloc(n2 * sizeof(int));
	for (int i = 0; i < n2; i++) {
		matr2[i] = (int*)malloc(m2 * sizeof(int));
		for (int j = 0; j < m2; j++) {
			printf("Element [%d][%d] = ", i + 1, j + 1);
			scanf_s("%d", &matr2[i][j]);
		}
	}
	PrintMatr(matr1, n1, m1);
	PrintMatr(matr2, n2, m2);
	int** matr = MultMatr(matr1, n1, m1, matr2, n2, m2);
	PrintMatr(matr, n1, m2);

	getchar();
	return 0;
}