#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create and traverse the circular linked list
int main() {
    int n, value;
    struct Node *head = NULL, *temp = NULL, *newNode = NULL;

    // Read the number of elements
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        
        // Allocate memory for the new node
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;

        if (head == NULL) {
            head = newNode;
            newNode->next = head; // Point to itself to maintain circularity
            temp = head;
        } else {
            temp->next = newNode;
            newNode->next = head; // Last node always points to head
            temp = newNode;
        }
    }

    // Traversal
    if (head != NULL) {
        struct Node* current = head;
        do {
            printf("%d ", current->data);
            current = current->next;
        } while (current != head); // Stop when we wrap back to the start
    }

    return 0;
}
