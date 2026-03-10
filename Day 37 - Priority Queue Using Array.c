#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n;
    
    // Read the number of operations
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // Dynamically allocate array for the priority queue
    // The max possible size is 'n' if all operations are inserts
    int* pq = (int*)malloc(n * sizeof(int));
    int size = 0;

    for (int i = 0; i < n; i++) {
        char op[15];
        scanf("%s", op);

        if (strcmp(op, "insert") == 0) {
            int val;
            scanf("%d", &val);
            // Insert at the end of the array
            pq[size++] = val;
            
        } else if (strcmp(op, "delete") == 0) {
            if (size == 0) {
                printf("-1\n");
            } else {
                // Find the index of the highest priority (minimum value) element
                int min_idx = 0;
                for (int j = 1; j < size; j++) {
                    if (pq[j] < pq[min_idx]) {
                        min_idx = j;
                    }
                }
                
                // Print the deleted element
                printf("%d\n", pq[min_idx]);
                
                // Remove it by replacing it with the last element in the array
                pq[min_idx] = pq[size - 1];
                size--;
            }
            
        } else if (strcmp(op, "peek") == 0) {
            if (size == 0) {
                printf("-1\n");
            } else {
                // Find the index of the highest priority (minimum value) element
                int min_idx = 0;
                for (int j = 1; j < size; j++) {
                    if (pq[j] < pq[min_idx]) {
                        min_idx = j;
                    }
                }
                
                // Print the peeked element without removing it
                printf("%d\n", pq[min_idx]);
            }
        }
    }

    // Free the dynamically allocated memory
    free(pq);
    return 0;
}