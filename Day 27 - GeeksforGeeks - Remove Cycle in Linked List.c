#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

// Core function to remove the loop
void removeLoop(struct Node* head) {
    if (head == NULL || head->next == NULL) return;

    struct Node* slow = head;
    struct Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (slow == fast) {
        slow = head;
        if (slow == fast) {
            while (fast->next != slow) {
                fast = fast->next;
            }
        } else {
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        fast->next = NULL;
    }
}

// Helper function to check if a cycle exists
bool detectLoop(struct Node* head) {
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

int main() {
    int n, pos;
    
    printf("Enter the number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    struct Node** nodes = (struct Node**)malloc(n * sizeof(struct Node*));

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        nodes[i] = (struct Node*)malloc(sizeof(struct Node));
        scanf("%d", &nodes[i]->data);
        nodes[i]->next = NULL;
        if (i > 0) nodes[i-1]->next = nodes[i];
    }

    printf("Enter pos (index to connect tail to, -1 for no cycle): ");
    if (scanf("%d", &pos) == 1 && pos >= 0 && pos < n) {
        nodes[n-1]->next = nodes[pos];
    }

    // Check if loop exists initially
    bool hadLoop = detectLoop(nodes[0]);
    
    // Call the function to remove the loop
    removeLoop(nodes[0]);
    
    // Check if loop exists after removal attempt
    bool hasLoopNow = detectLoop(nodes[0]);

    // Print true if a loop was there and is now gone, otherwise false
    if (hadLoop && !hasLoopNow) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // Free memory safely now that any potential loops are broken
    for (int i = 0; i < n; i++) {
        free(nodes[i]);
    }
    free(nodes);

    return 0;
}