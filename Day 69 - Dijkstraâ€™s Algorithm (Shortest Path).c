#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// --- 1. Graph Data Structures ---

// A structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// A structure to represent the graph
struct Graph {
    int V;
    struct AdjListNode** adjList;
};

// --- 2. Min-Heap (Priority Queue) Data Structures ---

struct MinHeapNode {
    int v;
    int dist;
};

struct MinHeap {
    int size;
    int capacity;
    struct MinHeapNode** array;
};

// --- Graph Functions ---

struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct AdjListNode**)malloc(V * sizeof(struct AdjListNode*));
    for (int i = 0; i < V; ++i)
        graph->adjList[i] = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Since it's an undirected graph, add edge from dest to src as well
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// --- Min-Heap Functions ---

struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (minHeap->size == 0) return NULL;

    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    
    minHeap->array[0] = lastNode;
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void insertMinHeap(struct MinHeap* minHeap, int v, int dist) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i] = newMinHeapNode(v, dist);

    // Bubble up to maintain heap property
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// --- Dijkstra's Algorithm ---

void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[V];      
    
    // Initialize all distances as infinite (INT_MAX)
    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
    }
    
    // Distance to source is always 0
    dist[src] = 0;
    
    // Create the priority queue and insert the source vertex
    // Capacity is roughly E (we might insert duplicates in lazy Dijkstra)
    struct MinHeap* minHeap = createMinHeap(V * V); 
    insertMinHeap(minHeap, src, 0);

    while (!isEmpty(minHeap)) {
        // Extract the cheapest node
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        int current_dist = minHeapNode->dist;
        free(minHeapNode);

        // "Lazy Deletion" check: If we already found a shorter path to 'u', ignore this outdated record
        if (current_dist > dist[u]) continue;

        // Traverse through all adjacent vertices of u
        struct AdjListNode* temp = graph->adjList[u];
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;

            // Relaxation Step: If there is a shorter path to v through u
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                
                // Push the updated, shorter distance into the priority queue
                insertMinHeap(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print the calculated shortest distances
    printf("Vertex \t Minimum Distance from Source (%d)\n", src);
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%d \t INF\n", i);
        } else {
            printf("%d \t %d\n", i, dist[i]);
        }
    }
    
    // Free the remaining heap memory
    free(minHeap->array);
    free(minHeap);
}

// --- Helper to Free Graph ---
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        struct AdjListNode* curr = graph->adjList[i];
        while (curr != NULL) {
            struct AdjListNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    // Constructing a weighted graph
    //      (0)
    //     /   \
    //  4 /     \ 1
    //   /       \
    // (1)-------(2)
    //   \   2   /
    //  5 \     / 8
    //     \   /
    //      (3)
    
    int V = 4;
    struct Graph* graph = createGraph(V);
    
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 8);

    printf("Executing Dijkstra's Algorithm using a Priority Queue...\n\n");
    
    // Find shortest paths from Vertex 0
    dijkstra(graph, 0);

    freeGraph(graph);

    return 0;
}