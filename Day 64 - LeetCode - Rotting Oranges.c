#include <stdio.h>
#include <stdlib.h>

// --- LeetCode Solution Core ---
int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    
    int maxQueueSize = m * n;
    int* q_row = (int*)malloc(maxQueueSize * sizeof(int));
    int* q_col = (int*)malloc(maxQueueSize * sizeof(int));
    int* q_time = (int*)malloc(maxQueueSize * sizeof(int));
    int front = 0, rear = 0;
    
    int fresh_count = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) {
                q_row[rear] = i;
                q_col[rear] = j;
                q_time[rear] = 0;
                rear++;
            } else if (grid[i][j] == 1) {
                fresh_count++;
            }
        }
    }
    
    if (fresh_count == 0) {
        free(q_row); free(q_col); free(q_time);
        return 0;
    }
    
    int max_time = 0;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (front < rear) {
        int r = q_row[front];
        int c = q_col[front];
        int t = q_time[front];
        front++;
        
        max_time = t;
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0];
            int nc = c + dirs[i][1];
            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                grid[nr][nc] = 2;
                fresh_count--;
                q_row[rear] = nr;
                q_col[rear] = nc;
                q_time[rear] = t + 1;
                rear++;
            }
        }
    }
    
    free(q_row); free(q_col); free(q_time);
    
    if (fresh_count > 0) return -1;
    return max_time;
}

// --- Helper Functions for Local Testing ---

int** createMatrix(int rows, int cols, int values[]) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = values[i * cols + j];
        }
    }
    return matrix;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

int main() {
    // --- Test Case 1 ---
    // grid = [[2,1,1],
    //         [1,1,0],
    //         [0,1,1]]
    int m1 = 3, n1 = 3;
    int vals1[] = {
        2, 1, 1,
        1, 1, 0,
        0, 1, 1
    };
    int** grid1 = createMatrix(m1, n1, vals1);
    int colSize1[] = {n1, n1, n1};
    
    printf("Test Case 1:\n");
    int result1 = orangesRotting(grid1, m1, colSize1);
    printf("Minutes elapsed: %d (Expected: 4)\n\n", result1);

    // --- Test Case 2 ---
    // grid = [[2,1,1],
    //         [0,1,1],
    //         [1,0,1]]
    int m2 = 3, n2 = 3;
    int vals2[] = {
        2, 1, 1,
        0, 1, 1,
        1, 0, 1
    };
    int** grid2 = createMatrix(m2, n2, vals2);
    int colSize2[] = {n2, n2, n2};
    
    printf("Test Case 2:\n");
    int result2 = orangesRotting(grid2, m2, colSize2);
    printf("Minutes elapsed: %d (Expected: -1)\n", result2);

    freeMatrix(grid1, m1);
    freeMatrix(grid2, m2);

    return 0;
}