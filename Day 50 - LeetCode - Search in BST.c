#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (root == NULL || root->val == val) {
        return root;
    }
    
    if (val < root->val) {
        return searchBST(root->left, val);
    }
    
    return searchBST(root->right, val);
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

// Helper to print the tree in preorder (Root -> Left -> Right) to verify the returned subtree
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Free the allocated tree memory
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Build LeetCode Example 1: root = [4,2,7,1,3]
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

    int searchVal = 2;
    printf("Searching for node with value %d...\n\n", searchVal);
    
    struct TreeNode* result = searchBST(root, searchVal);

    if (result != NULL) {
        printf("Node found! The subtree rooted at %d (Preorder) is:\n", result->val);
        preorderTraversal(result);
        printf("\nExpected Output: \n2 1 3\n");
    } else {
        printf("Node not found.\n");
    }

    // Clean up memory
    freeTree(root);

    return 0;
}