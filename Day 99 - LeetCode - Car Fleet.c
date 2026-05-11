#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    double time;
} Car;

int compareCars(const void* a, const void* b) {
    Car* carA = (Car*)a;
    Car* carB = (Car*)b;
    return carB->pos - carA->pos;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    if (positionSize == 0) return 0;
    
    Car* cars = (Car*)malloc(positionSize * sizeof(Car));
    for (int i = 0; i < positionSize; i++) {
        cars[i].pos = position[i];
        cars[i].time = (double)(target - position[i]) / speed[i];
    }
    
    qsort(cars, positionSize, sizeof(Car), compareCars);
    
    int fleets = 0;
    double max_time = -1.0;
    
    for (int i = 0; i < positionSize; i++) {
        if (cars[i].time > max_time) {
            fleets++;
            max_time = cars[i].time;
        }
    }
    
    free(cars);
    return fleets;
}

int main() {
    int target1 = 12;
    int pos1[] = {10, 8, 0, 5, 3};
    int speed1[] = {2, 4, 1, 1, 3};
    int size1 = sizeof(pos1) / sizeof(pos1[0]);
    
    printf("Target: %d | Pos: [10, 8, 0, 5, 3] | Speed: [2, 4, 1, 1, 3]\n", target1);
    printf("Fleets:   %d\n", carFleet(target1, pos1, size1, speed1, size1));
    printf("Expected: 3\n\n");
    
    int target2 = 10;
    int pos2[] = {3};
    int speed2[] = {3};
    int size2 = sizeof(pos2) / sizeof(pos2[0]);
    
    printf("Target: %d | Pos: [3] | Speed: [3]\n", target2);
    printf("Fleets:   %d\n", carFleet(target2, pos2, size2, speed2, size2));
    printf("Expected: 1\n\n");
    
    int target3 = 100;
    int pos3[] = {0, 2, 4};
    int speed3[] = {4, 2, 1};
    int size3 = sizeof(pos3) / sizeof(pos3[0]);
    
    printf("Target: %d | Pos: [0, 2, 4] | Speed: [4, 2, 1]\n", target3);
    printf("Fleets:   %d\n", carFleet(target3, pos3, size3, speed3, size3));
    printf("Expected: 1\n");
    
    return 0;
}