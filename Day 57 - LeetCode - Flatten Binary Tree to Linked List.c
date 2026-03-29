#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
void flatten(struct TreeNode* root) {
    struct TreeNode* curr = root;
    
    while (curr != NULL) {
        if (curr->left != NULL) {
            struct TreeNode* runner = curr->left;
            while (runner->right != NULL) {
                runner = runner->right;
            }
            
            runner->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }
        curr = curr->right;
    }
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

// Helper to print the flattened "linked list"
void printFlattenedList(struct TreeNode* root) {
    struct TreeNode* curr = root;
    while (curr != NULL) {
        printf("%d", curr->val);
        // Verify left pointer is completely gone
        if (curr->left != NULL) {
            printf(" [ERROR: Left pointer not NULL!] ");
        }
        if (curr->right != NULL) {
            printf(" -> ");
        }
        curr = curr->right;
    }
    printf("\n");
}

// Free the allocated tree memory
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Build LeetCode Example 1: root = [1,2,5,3,4,null,6]
    //          1
    //        /   \
    //       2     5
    //      / \     \
    //     3   4     6
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(5);
    
    root->left->left = createNode(3);
    root->left->right = createNode(4);
    
    root->right->right = createNode(6);

    printf("Flattening the tree...\n\n");
    
    flatten(root);

    printf("Flattened Linked List: ");
    printFlattenedList(root);
    printf("Expected Output:       1 -> 2 -> 3 -> 4 -> 5 -> 6\n");

    // Clean up memory
    freeTree(root);

    return 0;
}