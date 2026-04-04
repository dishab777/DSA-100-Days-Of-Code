#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dfs(int room, int** rooms, int* roomsColSize, bool* visited, int* count) {
    visited[room] = true;
    (*count)++;
    
    for (int i = 0; i < roomsColSize[room]; i++) {
        int next_room = rooms[room][i];
        if (!visited[next_room]) {
            dfs(next_room, rooms, roomsColSize, visited, count);
        }
    }
}

bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize) {
    bool* visited = (bool*)calloc(roomsSize, sizeof(bool));
    int count = 0;
    
    dfs(0, rooms, roomsColSize, visited, &count);
    
    bool result = (count == roomsSize);
    free(visited);
    
    return result;
}

int main() {
    printf("--- Test Case 1 ---\n");
    int n1 = 4;
    int* rooms1[4];
    
    int r1_0[] = {1}; rooms1[0] = r1_0;
    int r1_1[] = {2}; rooms1[1] = r1_1;
    int r1_2[] = {3}; rooms1[2] = r1_2;
    rooms1[3] = NULL; 
    
    int colSize1[] = {1, 1, 1, 0};
    
    bool result1 = canVisitAllRooms(rooms1, n1, colSize1);
    printf("Can visit all rooms? %s\n", result1 ? "true" : "false");
    printf("Expected:            true\n\n");

    printf("--- Test Case 2 ---\n");
    int n2 = 4;
    int* rooms2[4];
    
    int r2_0[] = {1, 3}; rooms2[0] = r2_0;
    int r2_1[] = {3, 0, 1}; rooms2[1] = r2_1;
    int r2_2[] = {2}; rooms2[2] = r2_2;
    int r2_3[] = {0}; rooms2[3] = r2_3;
    
    int colSize2[] = {2, 3, 1, 1};
    
    bool result2 = canVisitAllRooms(rooms2, n2, colSize2);
    printf("Can visit all rooms? %s\n", result2 ? "true" : "false");
    printf("Expected:            false\n");

    return 0;
}