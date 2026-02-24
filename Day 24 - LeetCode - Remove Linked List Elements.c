#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Function to remove all elements with a specific value
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* current = &dummy;
    
    while (current->next != NULL) {
        if (current->next->val == val) {
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp); // Free the memory of the removed node
        } else {
            current = current->next;
        }
    }
    
    return dummy.next;
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
    if (scanf("%d", &n) != 1 || n < 0) {
        return 0;
    }

    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;

    if (n > 0) {
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
    }

    int valToRemove;
    printf("Enter the value to remove: ");
    if (scanf("%d", &valToRemove) != 1) return 1;

    // Call the function
    head = removeElements(head, valToRemove);

    // Print the modified linked list
    printf("Modified List: ");
    struct ListNode* current = head;
    if (current == NULL) {
        printf("Empty List");
    }
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");

    // Free the remaining dynamically allocated memory
    while (head != NULL) {
        struct ListNode* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}