#include <stdio.h>
#define MAX  1000000
#define NUM 20000
int pos[MAX];

int BinSearch(int arr[], int left, int right, int key) {
	int mid = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] > key)
			right = mid - 1;
		else if (arr[mid] < key)
			left = mid + 1;
		else
			return mid;
	}
	return 0;
}

void swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

int partition(int arr[], int low, int high) {
	int pivot = arr[high], i = low;
	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			int temp = pos[j];
			pos[j] = pos[i];
			pos[i] = temp;
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[high]);
	int temp = pos[i];
	pos[i] = pos[high];
	pos[high] = temp;
	return i;
}

void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int k = partition(arr, low, high);
		quickSort(arr, low, k - 1);
		quickSort(arr, k + 1, high);
	}
}

int main() {
	int left = 1;
	int right, num, key;

	scanf ("%d", &right);
	int arr[right];
	for (int i = 1; i <= right; i++) {
		scanf("%d", arr + i);
		pos[i] = i;
	};

	quickSort(arr, left, right);
	scanf ("%d", &num);
	for (int i = 0; i < num; i++) {
		scanf ("%d", &key);
		int k = BinSearch(arr, left, right, key);
		printf("%d\n", pos[k]);
	};
	return 0;
}

