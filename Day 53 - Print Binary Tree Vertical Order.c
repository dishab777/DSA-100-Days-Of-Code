#include <stdio.h>
#include <stdlib.h>

// Define the Binary Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Queue item to store the node and its horizontal distance (HD)
typedef struct {
    struct Node* node;
    int hd;
} QueueItem;

// Dynamic array structure to hold nodes at a specific horizontal distance
typedef struct {
    int* values;
    int count;
    int capacity;
} Column;

// Function to create a new tree node
struct Node* createNode(int data) {
    if (data == -1) return NULL;
    
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to construct the tree from level order array using a queue
struct Node* constructTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = createNode(arr[0]);
    struct Node** queue = (struct Node**)malloc(n * sizeof(struct Node*));
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    int i = 1;

    while (front < rear && i < n) {
        struct Node* curr = queue[front++];

        if (i < n && arr[i] != -1) {
            curr->left = createNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr->right = createNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }
    free(queue);
    return root;
}

// Function to perform Vertical Order Traversal
void verticalOrder(struct Node* root, int n) {
    if (root == NULL) return;

    // The maximum possible horizontal spread is [-n, +n]. 
    // We offset the array index by 'n' to handle negative horizontal distances safely.
    int maxSpread = 2 * n + 1;
    Column* columns = (Column*)malloc(maxSpread * sizeof(Column));
    for (int i = 0; i < maxSpread; i++) {
        columns[i].capacity = 10; // Start with a small capacity
        columns[i].values = (int*)malloc(columns[i].capacity * sizeof(int));
        columns[i].count = 0;
    }

    int offset = n; 
    int min_hd = offset; // Keep track of the leftmost vertical line seen
    int max_hd = offset; // Keep track of the rightmost vertical line seen

    // Setup Queue for BFS
    QueueItem* queue = (QueueItem*)malloc(n * sizeof(QueueItem));
    int front = 0, rear = 0;

    queue[rear].node = root;
    queue[rear].hd = 0;
    rear++;

    while (front < rear) {
        QueueItem current = queue[front++];
        struct Node* currNode = current.node;
        int hd = current.hd;

        // Shift the index to safely store it in our array
        int index = hd + offset;
        
        // Track our actual horizontal boundaries
        if (index < min_hd) min_hd = index;
        if (index > max_hd) max_hd = index;

        // Resize the dynamic array if it gets full
        if (columns[index].count == columns[index].capacity) {
            columns[index].capacity *= 2;
            columns[index].values = (int*)realloc(columns[index].values, columns[index].capacity * sizeof(int));
        }
        
        // Add the current node's data to its corresponding vertical column
        columns[index].values[columns[index].count++] = currNode->data;

        // Enqueue left and right children with updated HDs
        if (currNode->left != NULL) {
            queue[rear].node = currNode->left;
            queue[rear].hd = hd - 1;
            rear++;
        }
        if (currNode->right != NULL) {
            queue[rear].node = currNode->right;
            queue[rear].hd = hd + 1;
            rear++;
        }
    }

    // Print the columns from leftmost HD to rightmost HD
    for (int i = min_hd; i <= max_hd; i++) {
        if (columns[i].count > 0) {
            for (int j = 0; j < columns[i].count; j++) {
                printf("%d ", columns[i].values[j]);
            }
            printf("\n");
        }
    }

    // Clean up memory
    for (int i = 0; i < maxSpread; i++) {
        free(columns[i].values);
    }
    free(columns);
    free(queue);
}

// Helper to free the tree memory
void freeTree(struct Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int* arr = (int*)malloc(n * sizeof(int));

    // Read the level order elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Construct the binary tree
    struct Node* root = constructTree(arr, n);

    // Perform the Vertical Order Traversal
    verticalOrder(root, n);

    // Clean up
    free(arr);
    freeTree(root);

    return 0;
}