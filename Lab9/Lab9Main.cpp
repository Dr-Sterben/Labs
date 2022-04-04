#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    int m, i, j, d;
    int** mas;
    printf("Enter matrix size ");
    scanf_s("%d", &m);
    mas = (int**)malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) { //ввод матрицы
        mas[i] = (int*)malloc(m * sizeof(int));
        for (j = 0; j < m; j++) {
            printf("mas[%d][%d]= ", i, j);
            scanf_s("%d", &mas[i][j]);
        }
    }
    PrintMatr(mas, m);
    d = DetMatr(mas, m);
    printf("Determinant is %d", d);
    free(mas);
    return 0;
}