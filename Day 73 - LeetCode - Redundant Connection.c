#include <stdio.h>
#include <stdlib.h>

int find(int* parent, int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]); 
}

void unionSet(int* parent, int* rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int n = edgesSize; 
    int* parent = (int*)malloc((n + 1) * sizeof(int));
    int* rank = (int*)calloc((n + 1), sizeof(int));
    
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }
    
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        
        if (find(parent, u) == find(parent, v)) {
            result[0] = u;
            result[1] = v;
            break; 
        } else {
            unionSet(parent, rank, u, v);
        }
    }
    
    free(parent);
    free(rank);
    return result;
}

int** createEdges(int size, int raw[][2]) {
    if (size == 0) return NULL;
    int** edges = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        edges[i] = (int*)malloc(2 * sizeof(int));
        edges[i][0] = raw[i][0];
        edges[i][1] = raw[i][1];
    }
    return edges;
}

void freeEdges(int** edges, int size) {
    for (int i = 0; i < size; i++) free(edges[i]);
    free(edges);
}

int main() 
{    
    int size = 5;
    int raw[][2] = 
    {
        {1, 2}, 
        {2, 3}, 
        {3, 4}, 
        {1, 4}, 
        {1, 5}
    };
    
    int** edges = createEdges(size, raw);
    
    printf("Evaluating graph for redundant connections using Union-Find...\n\n");
    
    int returnSize;
    int* result = findRedundantConnection(edges, size, NULL, &returnSize);
    
    printf("Redundant Edge Found: [%d, %d]\n", result[0], result[1]);
    printf("Expected Output:      [1, 4]\n");
    
    freeEdges(edges, size);
    free(result);

    return 0;
}