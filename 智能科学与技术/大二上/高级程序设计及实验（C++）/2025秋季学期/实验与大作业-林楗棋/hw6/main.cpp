#include "array.h"
#include "stdio.h"

int main() {
    Array<int> arr(10);
    for (int i = 0; i < 20; i++)
    {
       arr.put(i, i); 
    }
    for (int i = 0;i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}