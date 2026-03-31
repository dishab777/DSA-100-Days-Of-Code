#include <stdio.h>
#include <stdlib.h>

// Define the Binary Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Linear search to find the index of a value in the inorder array
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive helper function to construct the tree
struct Node* buildTreeUtil(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    // Base case: If the start index exceeds the end index, there is no subtree
    if (inStart > inEnd) {
        return NULL;
    }

    // Pick the current node from the end of the Postorder traversal and decrement the index
    struct Node* node = createNode(postorder[*postIndex]);
    (*postIndex)--;

    // If this node has no children (it's a leaf node), return it
    if (inStart == inEnd) {
        return node;
    }

    // Find the index of this node in the Inorder traversal
    int inIndex = search(inorder, inStart, inEnd, node->data);

    // CRITICAL REVERSAL: When reading postorder backwards, we process the RIGHT subtree first!
    node->right = buildTreeUtil(inorder, postorder, inIndex + 1, inEnd, postIndex);
    node->left = buildTreeUtil(inorder, postorder, inStart, inIndex - 1, postIndex);

    return node;
}

// Wrapper function to initialize the postorder index at the very end of the array
struct Node* buildTree(int inorder[], int postorder[], int n) {
    int postIndex = n - 1;
    return buildTreeUtil(inorder, postorder, 0, n - 1, &postIndex);
}

// Function to print the Preorder Traversal (Root -> Left -> Right)
void printPreorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

// Helper to free the tree memory
void freeTree(struct Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int* inorder = (int*)malloc(n * sizeof(int));
    int* postorder = (int*)malloc(n * sizeof(int));

    // Read the Inorder elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    // Read the Postorder elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }

    // Construct the binary tree
    struct Node* root = buildTree(inorder, postorder, n);

    // Print the Preorder traversal
    printPreorder(root);
    printf("\n");

    // Clean up
    free(inorder);
    free(postorder);
    freeTree(root);

    return 0;
}