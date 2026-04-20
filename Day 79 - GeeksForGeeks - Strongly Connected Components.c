#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Stack {
    int* arr;
    int top;
} Stack;

void push(Stack* st, int val) {
    st->arr[++(st->top)] = val;
}

int pop(Stack* st) {
    return st->arr[(st->top)--];
}

void addEdge(Node** adjList, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

void dfs1(int u, Node** adj, bool* vis, Stack* st) {
    vis[u] = true;
    
    Node* curr = adj[u];
    while (curr != NULL) {
        int v = curr->dest;
        if (!vis[v]) {
            dfs1(v, adj, vis, st);
        }
        curr = curr->next;
    }
    
    push(st, u);
}

void dfs2(int u, Node** adjT, bool* vis) {
    vis[u] = true;
    
    Node* curr = adjT[u];
    while (curr != NULL) {
        int v = curr->dest;
        if (!vis[v]) {
            dfs2(v, adjT, vis);
        }
        curr = curr->next;
    }
}

int kosaraju(int V, int** edges, int E) {
    Node** adj = (Node**)calloc(V, sizeof(Node*));
    Node** adjT = (Node**)calloc(V, sizeof(Node*));

    // Build both graphs simultaneously
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(adj, u, v);
        addEdge(adjT, v, u);
    }

    bool* vis = (bool*)calloc(V, sizeof(bool));
    
    Stack st;
    st.arr = (int*)malloc(V * sizeof(int));
    st.top = -1;

    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            dfs1(i, adj, vis, &st);
        }
    }

    for (int i = 0; i < V; i++) {
        vis[i] = false;
    }

    int sccCount = 0;
    while (st.top != -1) {
        int u = pop(&st);

        if (!vis[u]) {
            sccCount++;
            dfs2(u, adjT, vis);
        }
    }

    for (int i = 0; i < V; i++) {
        Node* curr = adj[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        curr = adjT[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adj);
    free(adjT);
    free(vis);
    free(st.arr);

    return sccCount;
}

int** createEdges(int E, int raw[][2]) {
    int** edges = (int**)malloc(E * sizeof(int*));
    for (int i = 0; i < E; i++) {
        edges[i] = (int*)malloc(2 * sizeof(int));
        edges[i][0] = raw[i][0];
        edges[i][1] = raw[i][1];
    }
    return edges;
}

void freeEdges(int** edges, int E) {
    for (int i = 0; i < E; i++) free(edges[i]);
    free(edges);
}

int main() {
    
    int V = 5;
    int E = 5;
    int raw[][2] = {
        {0, 2}, 
        {2, 1}, 
        {1, 0}, 
        {2, 3}, 
        {3, 4}
    };

    int** edges = createEdges(E, raw);

    printf("Executing Kosaraju's Algorithm in C...\n\n");
    
    int scc = kosaraju(V, edges, E);
    
    printf("Number of Strongly Connected Components: %d\n", scc);
    printf("Expected Output:                         3\n");

    freeEdges(edges, E);

    return 0;
}