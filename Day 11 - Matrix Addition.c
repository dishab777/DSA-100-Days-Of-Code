#include <stdio.h>

int main() {
    int m, n;
    int a[100][100];
    int b[100][100];
    // Read dimensions
    if (scanf("%d %d", &m, &n) != 2) return 1;

    // Read first matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Read second matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // Add and print result
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", a[i][j] + b[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}