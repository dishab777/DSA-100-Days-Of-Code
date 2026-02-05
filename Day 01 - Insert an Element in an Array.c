#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[10001];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pos, x;
    scanf("%d", &pos);
    scanf("%d", &x);

    int index = pos - 1;

    for (int i = n; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = x;

    for (int i = 0; i < n + 1; i++) {
        printf("%d", arr[i]);
        if (i < n) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}