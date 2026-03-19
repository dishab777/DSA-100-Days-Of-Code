#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- Solution Core ---
int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;
    
    int leftHeight = maxDepth(root->left);
    int rightHeight = maxDepth(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// --- Helper Functions for Local Testing ---
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Build a test tree: 
    //      3
    //     / \
    //    9  20
    //       / \
    //      15  7
    struct TreeNode* root = createNode(3);
    root->left = createNode(9);
    root->right = createNode(20);
    root->right->left = createNode(15);
    root->right->right = createNode(7);

    int height = maxDepth(root);

    printf("Height of the Binary Tree: %d\n", height);
    printf("Expected Height:           3\n");

    // Clean up memory
    freeTree(root);

    return 0;
}