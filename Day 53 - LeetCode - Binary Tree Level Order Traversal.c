#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// --- LeetCode Solution Core ---
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    // Allocate memory for the 2D result array and column sizes
    int** result = (int**)malloc(2000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(2000 * sizeof(int));
    
    // Create a queue for BFS (Assuming a max of 2000 nodes total)
    struct TreeNode** queue = (struct TreeNode**)malloc(2000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    
    // Enqueue the root node
    queue[rear++] = root;
    
    while (front < rear) {
        // The number of elements currently in the queue is the exact size of the current level
        int levelSize = rear - front;
        
        // Record the size of this specific level
        (*returnColumnSizes)[*returnSize] = levelSize;
        
        // Allocate an array for the current level's values
        result[*returnSize] = (int*)malloc(levelSize * sizeof(int));
        
        // Process all nodes on the current level
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* curr = queue[front++];
            result[*returnSize][i] = curr->val;
            
            // Enqueue the children for the next level's iteration
            if (curr->left != NULL) queue[rear++] = curr->left;
            if (curr->right != NULL) queue[rear++] = curr->right;
        }
        
        // Move to the next level
        (*returnSize)++;
    }
    
    free(queue);
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
    // Build LeetCode Example 1: root = [3,9,20,null,null,15,7]
    //      3
    //     / \
    //    9  20
    //       / \
    //      15  7
    struct TreeNode* root = createNode(3);
    root->left = createNode(9);
    root->right = createNode(20);
    root->right->left = createNode(15);
    root->right->right = createNode(7);

    int returnSize;
    int* returnColumnSizes;
    
    int** result = levelOrder(root, &returnSize, &returnColumnSizes);

    printf("Level Order Traversal Output:\n");
    printf("[\n");
    for (int i = 0; i < returnSize; i++) {
        printf("  [");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", result[i][j]);
            if (j < returnColumnSizes[i] - 1) printf(",");
        }
        printf("]\n");
    }
    printf("]\n");

    // Clean up dynamically allocated memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);
    freeTree(root);

    return 0;
}