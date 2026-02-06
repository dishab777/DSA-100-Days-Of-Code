#include <stdio.h>

int missingNum(int *arr, int size) {
    int n = size + 1;
    long long expected_sum = (long long)n * (n + 1) / 2;
    long long current_sum = 0;

    for (int i = 0; i < size; i++) {
        current_sum += arr[i];
    }

    return (int)(expected_sum - current_sum);
}

int main() {
    int n;
    // Input the range limit (e.g., 5 for range 1 to 5)
    if (scanf("%d", &n) != 1) return 1;

    // The array has n-1 elements
    int size = n - 1;
    int arr[100000]; 

    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d\n", missingNum(arr, size));

    return 0;
}