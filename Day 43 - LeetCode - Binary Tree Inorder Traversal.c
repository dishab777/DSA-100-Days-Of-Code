#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void inorderHelper(struct TreeNode* root, int* result, int* index) {
    if (root == NULL) return;
    inorderHelper(root->left, result, index);
    result[*index] = root->val;
    (*index)++;
    inorderHelper(root->right, result, index);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = countNodes(root);
    if (*returnSize == 0) return NULL;
    
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    int index = 0;
    inorderHelper(root, result, &index);
    
    return result;
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

// Print array utility
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}

int main() {
    // Build LeetCode Example 1: root = [1, null, 2, 3]
    //   1
    //    \
    //     2
    //    /
    //   3
    struct TreeNode* root = createNode(1);
    root->right = createNode(2);
    root->right->left = createNode(3);

    int returnSize;
    int* result = inorderTraversal(root, &returnSize);

    printf("Inorder Traversal Result: ");
    printArray(result, returnSize);
    printf("Expected Result:          [1,3,2]\n");

    // Clean up memory
    free(result);
    freeTree(root);

    return 0;
}