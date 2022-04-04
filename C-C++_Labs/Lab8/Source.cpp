#include <stdio.h>

int max_arr(int* arr, int start, int end) {
	int result = arr[start];
	for (int i = start; i < end + 1; i++)
		if (result < arr[i])
			result = arr[i];
	return result;
}

int min_arr(int* arr, int start, int end) {
	int result = arr[start];
	for (int i = start; i < end + 1; i++)
		if (result > arr[i])
			result = arr[i];
	return result;
}

int max2(int i1, int i2) {
	if (i1 < i2)
		return i2;
	else
		return i1;
}

int min2(int i1, int i2) {
	if (i1 > i2)
		return i2;
	else
		return i1;
}

int min5(int i1, int i2, int i3, int i4, int i5) {
	return min2(min2(min2(i1, i2), min2(i3, i4)), i5);
}

int max5(int i1, int i2, int i3, int i4, int i5) {
	return max2(max2(max2(i1, i2), max2(i3, i4)), i5);
}

void Saddle_points(int* arr) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (((arr[j + (5 * i)] == max_arr(arr, 5 * i, 5 * i + 4)) && (arr[j + (5 * i)] == (min5(arr[j], arr[j+5], arr[j+10], arr[j+15], arr[j+20]))))
				|| ((arr[j + (5 * i)] == min_arr(arr, 5 * i, 5 * i + 4)) && (arr[j + (5 * i)] == (max5(arr[j], arr[j + 5], arr[j + 10], arr[j + 15], arr[j + 20])))))
				printf("(%d, %d) ", j+1, i+1);
		}
	}
}
