#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AdjNode {
    int dest;
    int weight;
    struct AdjNode* next;
} AdjNode;

void addEdge(AdjNode** adjList, int u, int v, int w) {
    AdjNode* newNode1 = (AdjNode*)malloc(sizeof(AdjNode));
    newNode1->dest = v;
    newNode1->weight = w;
    newNode1->next = adjList[u];
    adjList[u] = newNode1;

    AdjNode* newNode2 = (AdjNode*)malloc(sizeof(AdjNode));
    newNode2->dest = u;
    newNode2->weight = w;
    newNode2->next = adjList[v];
    adjList[v] = newNode2;
}

typedef struct HeapNode {
    int dest;
    int weight;
} HeapNode;

typedef struct MinHeap {
    HeapNode* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* heap, int dest, int weight) {
    if (heap->size == heap->capacity) return; 
    
    int i = heap->size++;
    heap->array[i].dest = dest;
    heap->array[i].weight = weight;

    while (i != 0 && heap->array[(i - 1) / 2].weight > heap->array[i].weight) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode pop(MinHeap* heap) {
    if (heap->size <= 0) return (HeapNode){-1, -1};
    if (heap->size == 1) return heap->array[--heap->size];

    HeapNode root = heap->array[0];
    heap->array[0] = heap->array[--heap->size];
    
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < heap->size && heap->array[left].weight < heap->array[smallest].weight)
            smallest = left;
        if (right < heap->size && heap->array[right].weight < heap->array[smallest].weight)
            smallest = right;
            
        if (smallest != i) {
            swap(&heap->array[i], &heap->array[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

int primMST(int n, int m, AdjNode** adjList) {
    bool* inMST = (bool*)calloc(n + 1, sizeof(bool));
    
    MinHeap* heap = createMinHeap(2 * m); 
    
    int total_weight = 0;
    int edges_used = 0;
    
    push(heap, 1, 0);
    
    while (heap->size > 0 && edges_used < n) {
        HeapNode current = pop(heap);
        int u = current.dest;
        int w = current.weight;
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        total_weight += w;
        edges_used++;

        AdjNode* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->dest;
            int weight_uv = temp->weight;
            
    
            if (!inMST[v]) {
                push(heap, v, weight_uv);
            }
            temp = temp->next;
        }
    }
    
    free(inMST);
    free(heap->array);
    free(heap);
    
    return total_weight;
}

int main() {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    AdjNode** adjList = (AdjNode**)calloc(n + 1, sizeof(AdjNode*));
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(adjList, u, v, w);
    }
    
    int mst_weight = primMST(n, m, adjList);
    printf("%d\n", mst_weight);
    
    for (int i = 1; i <= n; i++) {
        AdjNode* curr = adjList[i];
        while (curr != NULL) {
            AdjNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(adjList);
    
    return 0;
}