#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int arr[10001];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pos;
    scanf("%d", &pos);

    int index = pos - 1;

    // Shift elements to the left to overwrite the element at 'pos'
    for (int i = index; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    // Print the updated array (n - 1 elements)
    for (int i = 0; i < n - 1; i++) {
        printf("%d", arr[i]);
        if (i < n - 2) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}