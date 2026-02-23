#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Function to detect a cycle using Floyd's Tortoise and Hare algorithm
bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true; // Cycle detected
        }
    }
    
    return false; // Reached the end of the list, no cycle
}

int main() {
    int n, pos;
    
    printf("Enter the number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("List is empty. Has cycle: false\n");
        return 0;
    }

    // We use an array of pointers to easily access nodes by index for creating the cycle
    struct ListNode** nodes = (struct ListNode**)malloc(n * sizeof(struct ListNode*));

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        nodes[i] = (struct ListNode*)malloc(sizeof(struct ListNode));
        nodes[i]->val = val;
        nodes[i]->next = NULL;
        
        // Link to the previous node
        if (i > 0) {
            nodes[i-1]->next = nodes[i];
        }
    }

    printf("Enter pos (index to connect tail to, -1 for no cycle): ");
    if (scanf("%d", &pos) == 1 && pos >= 0 && pos < n) {
        // Create the cycle by linking the last node to the node at index 'pos'
        nodes[n-1]->next = nodes[pos];
        printf("Cycle created connecting tail to node at index %d.\n", pos);
    } else {
        printf("No cycle created.\n");
    }

    // Check for cycle
    bool result = hasCycle(nodes[0]);

    printf("Result: %s\n", result ? "true" : "false");

    // Free memory safely using our array (to avoid infinite loops from the cycle)
    for (int i = 0; i < n; i++) {
        free(nodes[i]);
    }
    free(nodes);

    return 0;
}