#include <stdio.h>

// Function to find the maximum sum of a contiguous subsequence in an array
int maxSubsequenceSum(int arr[], int n) {
    // F[j] will store the maximum subsequence sum ending at position j
    int F[n];

    F[0] = arr[0];
    int maxSum = F[0];
    for (int j = 1; j < n; j++) {
        F[j] = (arr[j] > F[j-1] + arr[j]) ? arr[j] : F[j-1] + arr[j];
        if (F[j] > maxSum) {
            maxSum = F[j];
        }
    }

    return maxSum;
}

int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    int maxSum = maxSubsequenceSum(arr, n);
    printf("Maximum subsequence sum is: %d\n", maxSum);
    return 0;
}
