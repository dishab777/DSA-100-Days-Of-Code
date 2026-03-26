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

// Function to perform Zigzag (Spiral) Traversal
void zigzagTraversal(struct Node* root, int n) {
    if (root == NULL) return;

    // Allocate two stacks (maximum possible size is N)
    struct Node** s1 = (struct Node**)malloc(n * sizeof(struct Node*));
    struct Node** s2 = (struct Node**)malloc(n * sizeof(struct Node*));
    int top1 = -1, top2 = -1;

    // Push the root to the first stack
    s1[++top1] = root;
    int isFirst = 1;

    // Keep looping as long as there are nodes in either stack
    while (top1 >= 0 || top2 >= 0) {
        
        // Process Stack 1 (Prints Left to Right)
        while (top1 >= 0) {
            struct Node* curr = s1[top1--];
            
            if (!isFirst) printf(" ");
            printf("%d", curr->data);
            isFirst = 0;

            // Push left child, then right child to Stack 2
            if (curr->left != NULL) s2[++top2] = curr->left;
            if (curr->right != NULL) s2[++top2] = curr->right;
        }

        // Process Stack 2 (Prints Right to Left)
        while (top2 >= 0) {
            struct Node* curr = s2[top2--];
            
            if (!isFirst) printf(" ");
            printf("%d", curr->data);
            isFirst = 0;

            // Push right child, then left child to Stack 1
            if (curr->right != NULL) s1[++top1] = curr->right;
            if (curr->left != NULL) s1[++top1] = curr->left;
        }
    }
    printf("\n");

    // Clean up stack memory
    free(s1);
    free(s2);
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

    // Print the Zigzag traversal
    zigzagTraversal(root, n);

    // Clean up
    free(arr);
    freeTree(root);

    return 0;
}