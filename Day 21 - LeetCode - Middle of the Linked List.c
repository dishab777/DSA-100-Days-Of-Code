#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Function to find the middle node
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// Helper function to create a new node
struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

int main() {
    int n;
    printf("Enter the number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("List is empty.\n");
        return 0;
    }

    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct ListNode* newNode = createNode(val);
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Call the function
    struct ListNode* middle = middleNode(head);

    // Print the list starting from the middle node
    printf("Middle node to end: ");
    struct ListNode* current = middle;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");

    // Free memory
    current = head;
    while (current != NULL) {
        struct ListNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}