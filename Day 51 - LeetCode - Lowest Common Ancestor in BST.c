#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL) return NULL;
    
    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    }
    
    if (p->val > root->val && q->val > root->val) {
        return lowestCommonAncestor(root->right, p, q);
    }
    
    return root;
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
    // Build LeetCode Example 1: root = [6,2,8,0,4,7,9,null,null,3,5]
    //            6
    //          /   \
    //         2     8
    //        / \   / \
    //       0   4 7   9
    //          / \
    //         3   5
    struct TreeNode* root = createNode(6);
    root->left = createNode(2);
    root->right = createNode(8);
    
    root->left->left = createNode(0);
    root->left->right = createNode(4);
    root->left->right->left = createNode(3);
    root->left->right->right = createNode(5);
    
    root->right->left = createNode(7);
    root->right->right = createNode(9);

    // We need actual node pointers for p and q to pass to the function
    struct TreeNode* p = root->left;       // Node with value 2
    struct TreeNode* q = root->right;      // Node with value 8

    printf("Finding the LCA of %d and %d...\n", p->val, q->val);
    
    struct TreeNode* lca = lowestCommonAncestor(root, p, q);

    if (lca != NULL) {
        printf("Lowest Common Ancestor: %d\n", lca->val);
        printf("Expected Output:        6\n");
    } else {
        printf("LCA not found.\n");
    }

    // Clean up memory
    freeTree(root);

    return 0;
}