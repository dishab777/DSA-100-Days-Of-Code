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
    if (root == NULL || root == p || root == q) {
        return root;
    }
    
    struct TreeNode* leftLCA = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* rightLCA = lowestCommonAncestor(root->right, p, q);
    
    if (leftLCA != NULL && rightLCA != NULL) {
        return root;
    }
    
    return (leftLCA != NULL) ? leftLCA : rightLCA;
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
    // Build LeetCode Example 1: root = [3,5,1,6,2,0,8,null,null,7,4]
    //             3
    //          /     \
    //         5       1
    //        / \     / \
    //       6   2   0   8
    //          / \
    //         7   4
    struct TreeNode* root = createNode(3);
    
    root->left = createNode(5);
    root->right = createNode(1);
    
    root->left->left = createNode(6);
    root->left->right = createNode(2);
    root->left->right->left = createNode(7);
    root->left->right->right = createNode(4);
    
    root->right->left = createNode(0);
    root->right->right = createNode(8);

    // Grab the actual node pointers for p (value 5) and q (value 1)
    struct TreeNode* p = root->left;       
    struct TreeNode* q = root->right;      

    printf("Finding the LCA of node %d and node %d...\n", p->val, q->val);
    
    struct TreeNode* lca = lowestCommonAncestor(root, p, q);

    if (lca != NULL) {
        printf("Lowest Common Ancestor: %d\n", lca->val);
        printf("Expected Output:        3\n");
    } else {
        printf("LCA not found.\n");
    }

    // Clean up memory
    freeTree(root);

    return 0;
}