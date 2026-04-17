#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

void addEdge(Node** adjList, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
    
    newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = u;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

void dfs(Node** adjList, bool* visited, int curr) {
    visited[curr] = true;
    Node* temp = adjList[curr];
    while (temp != NULL) {
        int neighbor = temp->dest;
        if (!visited[neighbor]) {
            dfs(adjList, visited, neighbor);
        }
        temp = temp->next;
    }
}

int main() {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    Node** adjList = (Node**)calloc(n + 1, sizeof(Node*));
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adjList, u, v);
    }
    
    int connected_components = 0;
    
    for (int i = 1; i <= n; i++) {

        if (!visited[i]) {
            connected_components++;
    
            dfs(adjList, visited, i);
        }
    }
    
    printf("%d\n", connected_components);
    
    for (int i = 1; i <= n; i++) {
        Node* curr = adjList[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adjList);
    free(visited);
    
    return 0;
}