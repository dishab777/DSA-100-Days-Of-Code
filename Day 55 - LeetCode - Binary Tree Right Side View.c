#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
void dfsRightView(struct TreeNode* node, int level, int* max_level, int* result, int* returnSize) {
    if (node == NULL) return;

    if (level > *max_level) {
        result[(*returnSize)++] = node->val;
        *max_level = level;
    }

    dfsRightView(node->right, level + 1, max_level, result, returnSize);
    dfsRightView(node->left, level + 1, max_level, result, returnSize);
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (root == NULL) return NULL;
    
    int* result = (int*)malloc(100 * sizeof(int));
    int max_level = 0;
    
    dfsRightView(root, 1, &max_level, result, returnSize);
    
    return result;
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
    // Build LeetCode Example 1: root = [1,2,3,null,5,null,4]
    //      1
    //     / \
    //    2   3
    //     \   \
    //      5   4
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->right = createNode(5);
    root->right->right = createNode(4);

    int returnSize;
    
    // Call our function
    int* result = rightSideView(root, &returnSize);

    // Print the results
    printf("Right Side View Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) printf(", ");
    }
    printf("]\n");

    printf("Expected Output:        [1, 3, 4]\n");

    // Clean up dynamically allocated memory
    free(result);
    freeTree(root);

    return 0;
}