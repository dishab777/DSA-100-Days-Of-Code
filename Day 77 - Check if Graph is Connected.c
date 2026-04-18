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

// --- DFS Traversal Logic ---

void dfs(Node** adjList, bool* visited, int curr, int* count) {
    visited[curr] = true;
    (*count)++;
    
    Node* temp = adjList[curr];
    while (temp != NULL) {
        int neighbor = temp->dest;
        if (!visited[neighbor]) {
            dfs(adjList, visited, neighbor, count);
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
    
    int visited_count = 0;
    
    if (n > 0) {
        dfs(adjList, visited, 1, &visited_count);
    }
    
    if (visited_count == n) {
        printf("CONNECTED\n");
    } else {
        printf("NOT CONNECTED\n");
    }
    
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