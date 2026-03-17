#include <stdio.h>
#include <stdlib.h>

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

// --- Traversals ---

void inorder(struct Node* root, int* isFirst) {
    if (root == NULL) return;
    inorder(root->left, isFirst);
    
    if (!(*isFirst)) printf(" ");
    printf("%d", root->data);
    *isFirst = 0;
    
    inorder(root->right, isFirst);
}

void preorder(struct Node* root, int* isFirst) {
    if (root == NULL) return;
    
    if (!(*isFirst)) printf(" ");
    printf("%d", root->data);
    *isFirst = 0;
    
    preorder(root->left, isFirst);
    preorder(root->right, isFirst);
}

void postorder(struct Node* root, int* isFirst) {
    if (root == NULL) return;
    
    postorder(root->left, isFirst);
    postorder(root->right, isFirst);
    
    if (!(*isFirst)) printf(" ");
    printf("%d", root->data);
    *isFirst = 0;
}

// --- Main Logic ---

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

    // 1. Inorder Traversal
    int first = 1;
    inorder(root, &first);
    printf("\n");

    // 2. Preorder Traversal
    first = 1;
    preorder(root, &first);
    printf("\n");

    // 3. Postorder Traversal
    first = 1;
    postorder(root, &first);
    printf("\n");

    // Clean up dynamic array
    free(arr);

    return 0;
}