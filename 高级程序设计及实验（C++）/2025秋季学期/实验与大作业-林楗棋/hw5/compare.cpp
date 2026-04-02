#include <iostream>
#include <cstdlib>
#include <ctime>

template <class T>
void insertionSort(T a[], int n) {
	for (int i = 1; i < n; ++i) {
		T temp = a[i];
		int j = i;
		while (j > 0 && temp < a[j - 1]) {
			a[j] = a[j - 1];
			--j;
		}
		a[j] = temp;
	}
}

template <class T>
void mySwap(T &x, T &y) {
	T temp = x;
	x = y;
	y = temp;
}

template <class T>
void selectionSort(T a[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		int leastIndex = i;
		for (int j = i + 1; j < n; ++j)
			if (a[j] < a[leastIndex])
				leastIndex = j;
		mySwap(a[i], a[leastIndex]);
	}
}

template <class T>
void bubbleSort(T a[], int n) {
	for (int i = n - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j)
			if (a[j + 1] < a[j])
				mySwap(a[j], a[j + 1]);
	}
}

int main() {
    srand(42);
    int iter = 2e3;
    int arr_len = 1e3;

    time_t start, end;
    start = clock();
    for (int i = 0;i < iter;i++) {
        int *arr1 = new int[arr_len];

        for (int j = 0; j < arr_len; j++) {
            arr1[j] = rand() % 1000;
        }        
        insertionSort(arr1, arr_len);
        delete[] arr1;
    }
    end = clock();
    std::cout << "插入排序耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << std::endl;

    start = clock();
    for (int i= 0;i < iter;i++) {
        int *arr1 = new int[arr_len];

        for (int j = 0; j < arr_len; j++) {
            arr1[j] = rand() % 1000;
        }        
        selectionSort(arr1, arr_len);
        delete[] arr1;
    }
    end = clock();
    std::cout << "选择排序耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << std::endl;

    start = clock();
    for (int i = 0;i < iter;i++) {
        int *arr1 = new int[arr_len];

        for (int j = 0; j < arr_len; j++) {
            arr1[j] = rand() % 1000;
        }        
        bubbleSort(arr1, arr_len);
        delete[] arr1;
    }
    end = clock();
    std::cout << "冒泡排序耗时：" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << std::endl;

}