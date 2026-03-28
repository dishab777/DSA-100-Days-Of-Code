#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the Binary Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    if (data == -1) return NULL; // -1 denotes a NULL node
    
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

        // Process Left Child
        if (i < n && arr[i] != -1) {
            curr->left = createNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;

        // Process Right Child
        if (i < n && arr[i] != -1) {
            curr->right = createNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }

    free(queue);
    return root;
}

// --- Solution Core ---
bool isMirror(struct Node* t1, struct Node* t2) {
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    
    return (t1->data == t2->data)
        && isMirror(t1->right, t2->left)
        && isMirror(t1->left, t2->right);
}

bool isSymmetric(struct Node* root) {
    if (root == NULL) return true;
    return isMirror(root->left, root->right);
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

    // Check symmetry and print result
    if (isSymmetric(root)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // Clean up
    free(arr);
    freeTree(root);

    return 0;
}