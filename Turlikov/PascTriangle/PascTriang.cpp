#include<stdio.h>
#include"Header.h"

int main() {
	int num = 0; char flag = 'q';
	printf("Enter line number of Pascal's triangle: ");
	scanf_s("%d", &num);
	printf("Do you need all triangle or just a line (a/l): ");
	while ((flag != 'a') && (flag != 'l'))
		flag = getchar();
	NLine(num, flag);
	return 0;
}