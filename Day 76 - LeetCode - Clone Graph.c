#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

struct Node* dfs(struct Node* node, struct Node** visited) {
    if (node == NULL) return NULL;
    
    if (visited[node->val] != NULL) {
        return visited[node->val];
    }
    
    struct Node* cloneNode = (struct Node*)malloc(sizeof(struct Node));
    cloneNode->val = node->val;
    cloneNode->numNeighbors = node->numNeighbors;
    
    visited[cloneNode->val] = cloneNode;
    
    cloneNode->neighbors = (struct Node**)malloc(node->numNeighbors * sizeof(struct Node*));
    
    for (int i = 0; i < node->numNeighbors; i++) {
        cloneNode->neighbors[i] = dfs(node->neighbors[i], visited);
    }
    
    return cloneNode;
}

struct Node* cloneGraph(struct Node *s) {
    if (s == NULL) return NULL;
    struct Node* visited[105] = {NULL};
    return dfs(s, visited);
}

struct Node* createNode(int val, int numNeighbors) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->numNeighbors = numNeighbors;
    newNode->neighbors = (struct Node**)malloc(numNeighbors * sizeof(struct Node*));
    return newNode;
}

void printGraphInfo(struct Node* node) {
    if (node == NULL) return;
    printf("Node Value: %d | Memory Address: %p\n", node->val, (void*)node);
    printf("Neighbors: ");
    for (int i = 0; i < node->numNeighbors; i++) {
        printf("%d ", node->neighbors[i]->val);
    }
    printf("\n\n");
}

int main() {
    struct Node* n1 = createNode(1, 1);
    struct Node* n2 = createNode(2, 1);
    
    n1->neighbors[0] = n2;
    n2->neighbors[0] = n1;
    
    printf("--- ORIGINAL GRAPH ---\n");
    printGraphInfo(n1);
    printGraphInfo(n2);
    
    struct Node* clonedGraph = cloneGraph(n1);
    
    struct Node* clonedN1 = clonedGraph;
    struct Node* clonedN2 = clonedGraph->neighbors[0];
    
    printf("--- CLONED GRAPH (Deep Copy) ---\n");
    printGraphInfo(clonedN1);
    printGraphInfo(clonedN2);
    
    return 0;
}