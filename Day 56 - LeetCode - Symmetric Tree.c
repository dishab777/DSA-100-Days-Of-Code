#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
bool isMirror(struct TreeNode* leftNode, struct TreeNode* rightNode) {
    if (leftNode == NULL && rightNode == NULL) return true;
    if (leftNode == NULL || rightNode == NULL) return false;
    
    return (leftNode->val == rightNode->val)
        && isMirror(leftNode->left, rightNode->right)
        && isMirror(leftNode->right, rightNode->left);
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;
    return isMirror(root->left, root->right);
}

// --- Helper Functions for Local Testing ---

// Create a new tree node manually
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Free the allocated tree memory
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Build LeetCode Example 1: root = [1,2,2,3,4,4,3]
    //          1
    //        /   \
    //       2     2
    //      / \   / \
    //     3   4 4   3
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(2);
    
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    
    root->right->left = createNode(4);
    root->right->right = createNode(3);

    printf("Checking if the tree is symmetric...\n");
    
    bool result = isSymmetric(root);

    printf("Result: %s\n", result ? "true" : "false");
    printf("Expected: true\n");

    // Clean up memory
    freeTree(root);

    return 0;
}