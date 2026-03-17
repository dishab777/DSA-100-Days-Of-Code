#include <stdio.h>
#include <stdlib.h>

// Define the structure for a Binary Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    if (data == -1) return NULL; // -1 represents NULL in this format
    
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
    
    // Array-based queue to hold Node pointers
    struct Node** queue = (struct Node**)malloc(n * sizeof(struct Node*));
    int front = 0, rear = 0;
    
    // Enqueue the root
    queue[rear++] = root;
    int i = 1;

    // Process the array elements
    while (front < rear && i < n) {
        // Dequeue the front node
        struct Node* curr = queue[front++];

        // 1. Process Left Child
        if (i < n && arr[i] != -1) {
            curr->left = createNode(arr[i]);
            queue[rear++] = curr->left; // Enqueue the newly created left child
        }
        i++;

        // 2. Process Right Child
        if (i < n && arr[i] != -1) {
            curr->right = createNode(arr[i]);
            queue[rear++] = curr->right; // Enqueue the newly created right child
        }
        i++;
    }

    free(queue);
    return root;
}

// Function for in-order traversal (Left, Root, Right)
void inorder(struct Node* root, int* isFirst) {
    if (root == NULL) return;
    
    inorder(root->left, isFirst);
    
    // Formatting to ensure space-separated output without a trailing space
    if (!(*isFirst)) {
        printf(" ");
    }
    printf("%d", root->data);
    *isFirst = 0;
    
    inorder(root->right, isFirst);
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

    // Print the in-order traversal
    int isFirst = 1;
    inorder(root, &isFirst);
    printf("\n");

    // Clean up dynamic array
    free(arr);

    return 0;
}