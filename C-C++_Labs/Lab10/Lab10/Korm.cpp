#include<stdio.h>
#include<stdlib.h>
int max2(int a, int b) {
	if (b < a)
		return b;
	else
		return a;
}
void zeroArr(char* arr, int a) {
	for (int i = 0; i < a; i++)
		arr[i] = '0';
}
char* AlphabetArr() {
	char* arr = (char*)malloc(59 * sizeof(char));
	for (int i = 65; i < 123; i++)
		arr[i - 65] = (char)i;
	arr[59] = 0;
	return arr;
}