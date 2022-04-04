#include <stdio.h>
#include <stdlib.h>

// m - ������ �������

void PrintMatr(int** mas, int m) { //������ ����� ���� �������
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", mas[i][j]);
        printf("\n");
    }
}

void SubMatr(int** mas, int** p, int i, int j, int m) { //mas  - �������� �������; p - ���� ���������� ����������; i, j - ������� ��������; m - ������ �������
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m - 1; ki++) { // �������� ��������� ������
        if (ki == i) di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++) { // �������� ��������� �������
            if (kj == j) dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}

int DetMatr(int** mas, int m) { //���������� ������������
    int i, j, d, k, n; //i - ������ �������, j - ������, d - ��� ������������
    int** p = (int**)malloc(m * sizeof(int*)); //p - ����������
    for (i = 0; i < m; i++)
        p[i] = (int*)malloc(m * sizeof(int));
    j = 0; d = 0;
    k = 1; //(-1) � ������� i
    n = m - 1; //���������� ������� ������� �� ����
    if (m < 1) {
        printf("Wrong size\n");
    }
    else if (m == 1) {
        d = mas[0][0];
        return(d);
    }
    else if (m == 2) {
        d = (mas[0][0] * mas[1][1]) - (mas[1][0] * mas[0][1]);
        return(d);
    }
    else if (m > 2) {
        for (i = 0; i < m; i++) {
            SubMatr(mas, p, i, 0, m);
            printf("%d\n", mas[i][j]);
            PrintMatr(p, n);
            d = d + k * mas[i][0] * DetMatr(p, n);
            k = -k;
        }
    }
    return(d);
}