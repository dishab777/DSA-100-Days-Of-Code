#include <stdio.h>
#include <stdlib.h>


void floydWarshall(int n, int** dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != -1 && dist[k][j] != -1) {
                    int detour_cost = dist[i][k] + dist[k][j];
                    if (dist[i][j] == -1 || detour_cost < dist[i][j]) {
                        dist[i][j] = detour_cost;
                    }
                }
            }
        }
    }
}


int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    floydWarshall(n, dist);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", dist[i][j]);
            if (j < n - 1) printf(" ");
        }
        printf("\n");
    }
    
    for (int i = 0; i < n; i++) {
        free(dist[i]);
    }
    free(dist);
    
    return 0;
}