#include <stdio.h>
#include <stdlib.h>

int main() {
    int p;
    if (scanf("%d", &p) != 1) return 1;

    int *arr1 = (int*)malloc(p * sizeof(int));
    for (int i = 0; i < p; i++) {
        scanf("%d", &arr1[i]);
    }

    int q;
    if (scanf("%d", &q) != 1) return 1;

    int *arr2 = (int*)malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) {
        scanf("%d", &arr2[i]);
    }

    int i = 0, j = 0;
    while (i < p && j < q) {
        if (arr1[i] < arr2[j]) {
            printf("%d ", arr1[i]);
            i++;
        } else {
            printf("%d ", arr2[j]);
            j++;
        }
    }

    while (i < p) {
        printf("%d ", arr1[i]);
        i++;
    }

    while (j < q) {
        printf("%d ", arr2[j]);
        j++;
    }
    printf("\n");

    free(arr1);
    free(arr2);
    return 0;
}