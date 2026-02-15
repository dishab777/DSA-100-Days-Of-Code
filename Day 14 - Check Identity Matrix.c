#include <stdio.h>

int main() {
    int n;
    int matrix[100][100];
    // Read size of the matrix
    if (scanf("%d", &n) != 1) return 1;
    
    int isIdentity = 1; // Flag, assume true initially

    // Read matrix elements and check condition simultaneously
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
            
            // Check diagonal elements (must be 1)
            if (i == j && matrix[i][j] != 1) {
                isIdentity = 0;
            }
            // Check non-diagonal elements (must be 0)
            else if (i != j && matrix[i][j] != 0) {
                isIdentity = 0;
            }
        }
    }

    if (isIdentity) {
        printf("Identity Matrix\n");
    } else {
        printf("Not an Identity Matrix\n");
    }

    return 0;
}