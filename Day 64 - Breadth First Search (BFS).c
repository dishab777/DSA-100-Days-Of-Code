#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the Linked List Node for the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Define the Graph structure
struct Graph {
    int numVertices;
    struct Node** adjLists; 
    bool* visited; 
};

// --- Graph Building Logic ---

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false; 
    }
    
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Insert at the HEAD of the linked list
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// --- BFS Traversal Logic ---

void BFS(struct Graph* graph, int startVertex) {
    // 1. Create a queue based on the number of vertices
    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = 0;

    // 2. Mark the starting vertex as visited and enqueue it
    graph->visited[startVertex] = true;
    queue[rear++] = startVertex;

    // 3. Loop until the queue is completely empty
    while (front < rear) {
        // Dequeue the front vertex and print it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct Node* temp = graph->adjLists[currentVertex];
        
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            
            // If an adjacent vertex has not been visited, mark it and enqueue it
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    
    // Clean up the queue
    free(queue);
}

// --- Helper Functions ---

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* curr = graph->adjLists[i];
        while (curr != NULL) {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}

int main() {
    // Example Input
    // 6 Vertices (0 to 5)
    int n = 6;
    
    struct Graph* graph = createGraph(n);

    // Adding edges to create the following graph:
    //      0
    //     / \
    //    1   2
    //   / \   \
    //  3   4   5
    
    // Note: Because we add to the head of the list, 0's list will be [2 -> 1].
    // BFS will visit 2 before 1.
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    int startVertex = 0;

    printf("Breadth-First Search starting from vertex %d:\n", startVertex);
    printf("Traversal Order: ");
    
    BFS(graph, startVertex);
    
    printf("\n");

    freeGraph(graph);

    return 0;
}