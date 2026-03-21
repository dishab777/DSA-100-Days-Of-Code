#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- Solution Core ---
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    if (root == NULL) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else if (val > root->val) {
        root->right = insertIntoBST(root->right, val);
    }
    
    return root;
}

// --- Helper Functions for Local Testing ---

// Helper function to print the tree in-order (Left -> Root -> Right)
// For a BST, this should print the elements in ascending order!
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    
    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

// Free the allocated tree memory
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct TreeNode* root = NULL;
    
    // Insert values into the BST
    // Let's build: 
    //        4
    //      /   \
    //     2     7
    //    / \   /
    //   1   3 5
    
    root = insertIntoBST(root, 4);
    root = insertIntoBST(root, 2);
    root = insertIntoBST(root, 7);
    root = insertIntoBST(root, 1);
    root = insertIntoBST(root, 3);
    root = insertIntoBST(root, 5);

    printf("In-order Traversal of the BST:\n");
    inorderTraversal(root);
    printf("\n");
    printf("Expected Output:\n1 2 3 4 5 7\n");

    // Clean up memory
    freeTree(root);

    return 0;
}