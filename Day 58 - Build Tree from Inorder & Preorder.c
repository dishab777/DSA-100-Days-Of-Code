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
struct Node* buildTreeUtil(int preorder[], int inorder[], int inStart, int inEnd, int* preIndex) {
    // Base case: If the start index exceeds the end index, there is no subtree to build
    if (inStart > inEnd) {
        return NULL;
    }

    // Pick the current node from the Preorder traversal and increment the index
    struct Node* node = createNode(preorder[*preIndex]);
    (*preIndex)++;

    // If this node has no children (it's a leaf node), return it
    if (inStart == inEnd) {
        return node;
    }

    // Find the index of this node in the Inorder traversal
    int inIndex = search(inorder, inStart, inEnd, node->data);

    // Using the index, build the left and right subtrees recursively
    node->left = buildTreeUtil(preorder, inorder, inStart, inIndex - 1, preIndex);
    node->right = buildTreeUtil(preorder, inorder, inIndex + 1, inEnd, preIndex);

    return node;
}

// Wrapper function to initialize the preorder index
struct Node* buildTree(int preorder[], int inorder[], int n) {
    int preIndex = 0;
    return buildTreeUtil(preorder, inorder, 0, n - 1, &preIndex);
}

// Function to print the Postorder Traversal (Left -> Right -> Root)
void printPostorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->data);
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

    int* preorder = (int*)malloc(n * sizeof(int));
    int* inorder = (int*)malloc(n * sizeof(int));

    // Read the Preorder elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    
    // Read the Inorder elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    // Construct the binary tree
    struct Node* root = buildTree(preorder, inorder, n);

    // Print the Postorder traversal
    printPostorder(root);
    printf("\n");

    // Clean up
    free(preorder);
    free(inorder);
    freeTree(root);

    return 0;
}