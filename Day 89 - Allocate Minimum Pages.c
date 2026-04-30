#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Core Logic ---

// Greedy check: Can we allocate books such that no student reads more than max_pages?
bool isValid(int* books, int n, int m, int max_pages) {
    int students_needed = 1;
    long long current_sum = 0;
    
    for (int i = 0; i < n; i++) {
        // If a single book is greater than the allowed limit, allocation is impossible
        if (books[i] > max_pages) {
            return false;
        }
        
        // If adding this book exceeds the limit, assign it to the NEXT student
        if (current_sum + books[i] > max_pages) {
            students_needed++;
            current_sum = books[i]; // The new student starts with this book
            
            // If we require more students than we have, this limit is too strict
            if (students_needed > m) {
                return false;
            }
        } else {
            // Otherwise, keep giving books to the current student
            current_sum += books[i];
        }
    }
    
    return true;
}

int findMinPages(int* books, int n, int m) {
    // Edge case: If there are more students than books, 
    // someone won't get a book, which violates the rules.
    if (m > n) {
        return -1; 
    }
    
    long long sum = 0;
    int max_val = 0;
    
    // Calculate the search boundaries
    for (int i = 0; i < n; i++) {
        sum += books[i];
        if (books[i] > max_val) {
            max_val = books[i];
        }
    }
    
    long long left = max_val; // Lowest possible answer
    long long right = sum;    // Highest possible answer
    long long best_limit = -1;
    
    // Binary Search on the Answer Space
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (isValid(books, n, m, mid)) {
            // It's possible! Save it, and try to find a STRICTER (smaller) maximum.
            best_limit = mid;
            right = mid - 1;
        } else {
            // Limit is too strict (requires too many students). We must increase it.
            left = mid + 1;
        }
    }
    
    return best_limit;
}

// --- Main Execution ---

int main() {
    int n, m;
    
    // Read number of books and students
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    // Dynamically allocate array for the books
    int* books = (int*)malloc(n * sizeof(int));
    if (books == NULL) return 1;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &books[i]);
    }
    
    // Compute and print the answer
    int result = findMinPages(books, n, m);
    printf("%d\n", result);
    
    free(books);
    return 0;
}