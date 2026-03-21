#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- Solution Core ---
int sumOfLeftLeaves(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    
    int sum = 0;
    
    if (root->left != NULL && root->left->left == NULL && root->left->right == NULL) {
        sum += root->left->val;
    } else {
        sum += sumOfLeftLeaves(root->left);
    }
    
    sum += sumOfLeftLeaves(root->right);
    
    return sum;
}

// --- Helper Functions for Local Testing ---

// Create a new tree node
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
    // Build LeetCode Example 1: root = [3,9,20,null,null,15,7]
    //        3
    //      /   \
    //     9    20
    //         /  \
    //        15   7
    //
    // The left leaves are 9 and 15. Sum = 24.
    struct TreeNode* root = createNode(3);
    root->left = createNode(9);
    root->right = createNode(20);
    root->right->left = createNode(15);
    root->right->right = createNode(7);

    int result = sumOfLeftLeaves(root);

    printf("Sum of Left Leaves: %d\n", result);
    printf("Expected Sum:       24\n");

    // Clean up memory
    freeTree(root);

    return 0;
}