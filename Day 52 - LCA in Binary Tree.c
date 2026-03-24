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

// Function to find the Lowest Common Ancestor
struct Node* findLCA(struct Node* root, int p, int q) {
    // 1. Base cases
    if (root == NULL) {
        return NULL;
    }
    if (root->data == p || root->data == q) {
        return root;
    }
    
    // 2. Recursively search left and right subtrees
    struct Node* leftLCA = findLCA(root->left, p, q);
    struct Node* rightLCA = findLCA(root->right, p, q);
    
    // 3. If both sides returned a valid node, THIS root is the LCA
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }
    
    // 4. Otherwise, pass up whichever side found a match
    if (leftLCA != NULL) {
        return leftLCA;
    } else {
        return rightLCA;
    }
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

    // Read the two target nodes
    int p, q;
    scanf("%d %d", &p, &q);

    // Construct the binary tree
    struct Node* root = constructTree(arr, n);

    // Find and print the LCA
    struct Node* lca = findLCA(root, p, q);
    if (lca != NULL) {
        printf("%d\n", lca->data);
    } else {
        printf("-1\n"); // Just in case LCA isn't found
    }

    // Clean up
    free(arr);
    freeTree(root);

    return 0;
}