#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    
    if (scanf("%d", &n) != 1) return 1;

    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        stack[++top] = val;
    }

    int m;
    if (scanf("%d", &m) != 1) {
        free(stack);
        return 1;
    }

    for (int i = 0; i < m; i++) {
        if (top >= 0) {
            top--;
        }
    }

    for (int i = top; i >= 0; i--) {
        printf("%d", stack[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");

    free(stack);
    return 0;
}