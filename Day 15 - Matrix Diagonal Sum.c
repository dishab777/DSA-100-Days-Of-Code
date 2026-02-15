#include <stdio.h>

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;

    int sum = 0;
    int element;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &element);
            if (i == j) {
                sum += element;
            }
        }
    }

    printf("%d\n", sum);

    return 0;
}