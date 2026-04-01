#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
int dfs(struct TreeNode* root, int* cameras) {
    if (root == NULL) return 2; 

    int leftState = dfs(root->left, cameras);
    int rightState = dfs(root->right, cameras);

    if (leftState == 0 || rightState == 0) {
        (*cameras)++;
        return 1;
    }

    if (leftState == 1 || rightState == 1) {
        return 2;
    }

    return 0;
}

int minCameraCover(struct TreeNode* root) {
    int cameras = 0;
    if (dfs(root, &cameras) == 0) {
        cameras++;
    }
    return cameras;
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
    // Build LeetCode Example 1: root = [0,0,null,0,0]
    //          0
    //         /
    //        0 (<- Optimal Camera Placement)
    //       / \
    //      0   0
    struct TreeNode* root = createNode(0);
    root->left = createNode(0);
    
    root->left->left = createNode(0);
    root->left->right = createNode(0);

    printf("Calculating minimum cameras required...\n\n");
    
    int result = minCameraCover(root);

    printf("Minimum Cameras: %d\n", result);
    printf("Expected:        1\n");

    // Clean up memory
    freeTree(root);

    return 0;
}