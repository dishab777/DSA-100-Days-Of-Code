#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- Solution Core ---
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (root == NULL || root->val == val) {
        return root;
    }
    
    if (root->val < val) {
        return searchBST(root->right, val);
    }
    
    return searchBST(root->left, val);
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
    // Build a sample BST:
    //        4
    //      /   \
    //     2     7
    //    / \
    //   1   3 
    struct TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(1);
    root->left->right = createNode(3);

    // Test Case 1: Search for a value that exists
    int target1 = 2;
    struct TreeNode* result1 = searchBST(root, target1);
    
    printf("Searching for %d...\n", target1);
    if (result1 != NULL) {
        printf("Found node with value: %d\n\n", result1->val);
    } else {
        printf("Node not found.\n\n");
    }

    // Test Case 2: Search for a value that does NOT exist
    int target2 = 5;
    struct TreeNode* result2 = searchBST(root, target2);
    
    printf("Searching for %d...\n", target2);
    if (result2 != NULL) {
        printf("Found node with value: %d\n", result2->val);
    } else {
        printf("Node not found. (Returned NULL as expected)\n");
    }

    // Clean up memory
    freeTree(root);

    return 0;
}