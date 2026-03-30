#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
struct TreeNode* buildUtil(int* preorder, int* preIndex, int* inorderMap, int inStart, int inEnd) {
    if (inStart > inEnd) return NULL;
    
    int rootVal = preorder[(*preIndex)++];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootVal;
    root->left = NULL;
    root->right = NULL;
    
    if (inStart == inEnd) return root;
    
    int inIndex = inorderMap[rootVal + 3000];
    
    root->left = buildUtil(preorder, preIndex, inorderMap, inStart, inIndex - 1);
    root->right = buildUtil(preorder, preIndex, inorderMap, inIndex + 1, inEnd);
    
    return root;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int inorderMap[6001] = {0};
    for (int i = 0; i < inorderSize; i++) {
        inorderMap[inorder[i] + 3000] = i;
    }
    
    int preIndex = 0;
    return buildUtil(preorder, &preIndex, inorderMap, 0, inorderSize - 1);
}

// --- Helper Functions for Local Testing ---

// Simple BFS Queue for printing Level Order
void printLevelOrder(struct TreeNode* root) {
    if (root == NULL) return;
    
    struct TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    printf("[");
    while (front < rear) {
        struct TreeNode* curr = queue[front++];
        if (curr != NULL) {
            printf("%d", curr->val);
            queue[rear++] = curr->left;
            queue[rear++] = curr->right;
        } else {
            printf("null");
        }
        
        // Don't print trailing commas for the last bunch of nulls
        if (front < rear) {
            int hasMoreValidNodes = 0;
            for(int i = front; i < rear; i++) {
                if(queue[i] != NULL) hasMoreValidNodes = 1;
            }
            if (hasMoreValidNodes) printf(",");
        }
    }
    printf("]\n");
}

// Free the allocated tree memory
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Example 1:
    // preorder = [3,9,20,15,7]
    // inorder = [9,3,15,20,7]
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[] = {9, 3, 15, 20, 7};
    int size = sizeof(preorder) / sizeof(preorder[0]);

    printf("Constructing the Binary Tree...\n\n");
    
    struct TreeNode* root = buildTree(preorder, size, inorder, size);

    printf("Level Order Output: ");
    printLevelOrder(root);
    printf("Expected Output:    [3,9,20,null,null,15,7]\n");

    // Clean up memory
    freeTree(root);

    return 0;
}