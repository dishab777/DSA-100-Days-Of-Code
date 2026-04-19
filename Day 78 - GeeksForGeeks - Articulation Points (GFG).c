#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void dfs(int u, int p, int** adj, int* adjColSize, int* tin, int* low, int* timer, int* mark) {
    tin[u] = low[u] = ++(*timer);
    int children = 0;
    
    for (int i = 0; i < adjColSize[u]; i++) {
        int v = adj[u][i];
        
        if (v == u) continue;
        if (v == p) continue;
        
        if (tin[v] != 0) {
            low[u] = MIN(low[u], tin[v]);
        } else {
            children++;
            dfs(v, u, adj, adjColSize, tin, low, timer, mark);
            
            low[u] = MIN(low[u], low[v]);
            
            if (p != -1 && low[v] >= tin[u]) {
                mark[u] = 1;
            }
        }
    }
    
    if (p == -1 && children > 1) {
        mark[u] = 1;
    }
}

int* articulationPoints(int V, int** adj, int* adjColSize, int* returnSize) {
    int* tin = (int*)calloc(V, sizeof(int));
    int* low = (int*)calloc(V, sizeof(int));
    int* mark = (int*)calloc(V, sizeof(int));
    int timer = 0;
    
    for (int i = 0; i < V; i++) {
        if (tin[i] == 0) {
            dfs(i, -1, adj, adjColSize, tin, low, &timer, mark);
        }
    }
    
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (mark[i] == 1) count++;
    }
    
    if (count == 0) {
        int* result = (int*)malloc(sizeof(int));
        result[0] = -1;
        *returnSize = 1;
        free(tin); free(low); free(mark);
        return result;
    }
    
    int* result = (int*)malloc(count * sizeof(int));
    int idx = 0;
    for (int i = 0; i < V; i++) {
        if (mark[i] == 1) {
            result[idx++] = i;
        }
    }
    
    *returnSize = count;
    free(tin); free(low); free(mark);
    
    return result;
}

int** createAdjList(int V, int* colSizes, int raw[][4]) {
    int** adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        if (colSizes[i] > 0) {
            adj[i] = (int*)malloc(colSizes[i] * sizeof(int));
            for (int j = 0; j < colSizes[i]; j++) {
                adj[i][j] = raw[i][j];
            }
        } else {
            adj[i] = NULL;
        }
    }
    return adj;
}

void freeAdjList(int** adj, int V) {
    for (int i = 0; i < V; i++) {
        free(adj[i]);
    }
    free(adj);
}

int main() {
    
    int V = 5;
    int colSizes[] = {2, 3, 2, 2, 1};
    int raw[][4] = {
        {1, 2},     
        {0, 2, 3},  
        {0, 1},     
        {1, 4},     
        {3}         
    };
    
    int** adj = createAdjList(V, colSizes, raw);
    
    printf("Evaluating Graph for Articulation Points...\n\n");
    
    int returnSize;
    int* result = articulationPoints(V, adj, colSizes, &returnSize);
    
    printf("Articulation Points Found: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\nExpected Output:           1 3\n");
    
    freeAdjList(adj, V);
    free(result);

    return 0;
}