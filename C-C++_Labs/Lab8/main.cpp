#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
	int* arr = (int*)malloc(25 * sizeof(int));
	printf("Please enter matrix:\n");
	for (int i = 0; i < 25; i = i+5)
		scanf_s("%d %d %d %d %d", &arr[i], &arr[i+1], &arr[i+2], &arr[i + 3], &arr[i + 4]);
	Saddle_points(arr);
	free(arr);
}
//умножение матриц произвольного размера