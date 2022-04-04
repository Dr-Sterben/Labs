#include<stdio.h>
#include<stdlib.h>

void NLine(int n, char flag) {
	if (n < 0) {
		printf("Wrong argumen");
		return;
	}
	else {
		unsigned long long int** matr = (unsigned long long int**)malloc((n + 1) * sizeof(unsigned long long int*));
		for (int i = 0; i < n + 1; i++) {
			matr[i] = (unsigned long long int*)malloc((n + 1) * sizeof(unsigned long long int));
			for (int j = 0; j < i + 1; j++) {
				if ((j == 0) || (j == i) || (i == 0))
					matr[i][j] = 1;
				else {
					matr[i][j] = matr[i - 1][j - 1] + matr[i - 1][j];
				}
			}
		}
		if (flag == 'l') {
			printf("%d: ", n);
			for (int i = 0; i < n + 1; i++)
				//printf("%llu ", matr[n][i]);
				printf("%llu\n", matr[n][i]);
			printf("\n");
		}
		else
			for (int i = 0; i < n + 1; i++) {
				printf("%d: ", i);
				for (int j = 0; j < i + 1; j++)
					//printf("%llu ", matr[i][j]);
					printf("%llu\n", matr[i][j]);
				printf("\n");
			}
		for (int i = 0; i < n; i++)
			free(matr[i]);
		free(matr);
	}
}