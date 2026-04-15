#include <stdio.h>
#include <stdlib.h>

int find(int* parent, int i) 
{
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]); 
}

int unionSet(int* parent, int* rank, int x, int y) 
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    
    if (rootX != rootY) 
    {
        if (rank[rootX] > rank[rootY]) 
        {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) 
        {
            parent[rootX] = rootY;
        } else 
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return 1; 
    }
    return 0; 
}

int countComponents(int n, int** edges, int edgesSize, int* edgesColSize) 
{
    int* parent = (int*)malloc(n * sizeof(int));
    int* rank = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; i++) 
    {
        parent[i] = i;
    }
    
    int components = n;
    
    for (int i = 0; i < edgesSize; i++) 
    {
        if (unionSet(parent, rank, edges[i][0], edges[i][1])) 
        {
            components--;
        }
    }
    
    free(parent);
    free(rank);
    
    return components;
}

int** createEdges(int size, int raw[][2]) 
{
    if (size == 0) return NULL;
    int** edges = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        edges[i] = (int*)malloc(2 * sizeof(int));
        edges[i][0] = raw[i][0];
        edges[i][1] = raw[i][1];
    }
    return edges;
}

void freeEdges(int** edges, int size) 
{
    for (int i = 0; i < size; i++) free(edges[i]);
    free(edges);
}

int main() 
{
    int n = 5;
    int size = 3;
    int raw[][2] = {
        {0, 1}, 
        {1, 2}, 
        {3, 4}
    };
    
    int** edges = createEdges(size, raw);
    
    printf("Counting Connected Components using Union-Find...\n\n");
    
    int result = countComponents(n, edges, size, NULL);
    
    printf("Total Connected Components: %d\n", result);
    printf("Expected Output:            2\n");
    
    freeEdges(edges, size);

    return 0;
}