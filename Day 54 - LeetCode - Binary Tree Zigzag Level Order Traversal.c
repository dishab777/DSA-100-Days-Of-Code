#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (root == NULL) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    int** result = (int**)malloc(2000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(2000 * sizeof(int));
    
    struct TreeNode** queue = (struct TreeNode**)malloc(2000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    bool leftToRight = true;
    
    while (front < rear) {
        int levelSize = rear - front;
        (*returnColumnSizes)[*returnSize] = levelSize;
        result[*returnSize] = (int*)malloc(levelSize * sizeof(int));
        
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* curr = queue[front++];
            
            int index = leftToRight ? i : (levelSize - 1 - i);
            result[*returnSize][index] = curr->val;
            
            if (curr->left != NULL) queue[rear++] = curr->left;
            if (curr->right != NULL) queue[rear++] = curr->right;
        }
        
        leftToRight = !leftToRight;
        (*returnSize)++;
    }
    
    free(queue);
    return result;
}

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct TreeNode* root = createNode(3);
    root->left = createNode(9);
    root->right = createNode(20);
    root->right->left = createNode(15);
    root->right->right = createNode(7);

    int returnSize;
    int* returnColumnSizes;
    
    int** result = zigzagLevelOrder(root, &returnSize, &returnColumnSizes);

    printf("Zigzag Level Order Traversal:\n");
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

    printf("\nExpected Output:\n[\n  [3]\n  [20,9]\n  [15,7]\n]\n");

    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);
    freeTree(root);

    return 0;
}