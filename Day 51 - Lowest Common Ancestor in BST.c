#include <stdio.h>
#include <stdlib.h>

// Define the Binary Tree Node
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
struct Node* insert(struct Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    }
    return root;
}

// Function to find the Lowest Common Ancestor in a BST
struct Node* findLCA(struct Node* root, int p, int q) {
    if (root == NULL) {
        return NULL;
    }
    
    // If both p and q are smaller than root, LCA is in the left subtree
    if (root->val > p && root->val > q) {
        return findLCA(root->left, p, q);
    }
    
    // If both p and q are greater than root, LCA is in the right subtree
    if (root->val < p && root->val < q) {
        return findLCA(root->right, p, q);
    }
    
    // We found the split point (or one of the nodes matches the root)
    return root;
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

    struct Node* root = NULL;

    // Read the array elements and build the BST
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    // Read the two target nodes
    int p, q;
    scanf("%d %d", &p, &q);

    // Find and print the LCA
    struct Node* lca = findLCA(root, p, q);
    if (lca != NULL) {
        printf("%d\n", lca->val);
    }

    // Clean up
    freeTree(root);

    return 0;
}