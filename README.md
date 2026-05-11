# 100 Days of Code: Data Structures & Algorithms in C 🚀

Welcome to my 100 Days of Code journey! This repository documents my progress, containing highly optimized, pure C implementations of classic and advanced algorithmic problems. 

Throughout this journey, I focused heavily on understanding the underlying mechanics of algorithms—moving beyond standard library functions to implement custom heaps, prefix sums, binary indexed trees, and divide-and-conquer logic entirely from scratch.

## 🧠 Core Paradigms Mastered

### 1. Binary Search on Answer Space
Mastered the technique of guessing an answer within a mathematical boundary and using a greedy check to narrow down the search space in $O(N \log M)$ time.
* Capacity To Ship Packages Within D Days
* Painter's Partition Problem
* Split Array Largest Sum

### 2. Sorting & Partitioning
Moved beyond basic sorts to write foundational logic and clever, single-pass array manipulations.
* **Standard Sorts:** Merge Sort, Quick Sort (Lomuto Partition), Insertion Sort.
* **Linear Sorts $O(N)$:** Counting Sort, Bucket Sort.
* **Advanced Partitioning:** Sort Colors (Dutch National Flag 3-Pointer technique), Kth Largest Element in an Array (Quickselect with 3-Way Partitioning to prevent $O(N^2)$ degradation).
* **Math/Bucketing:** Maximum Gap (Utilizing the Pigeonhole Principle to achieve $O(N)$ time without fully sorting).
* **Frequency Mapping:** Relative Sort Array.

### 3. Divide & Conquer (Modified Merge Sort)
Learned how to extract secondary information (like cross-array conditions and inversion counts) essentially for "free" while the array sorts itself.
* Count Inversions
* Reverse Pairs
* Count of Smaller Numbers After Self (Solved using both Struct-tracking Merge Sort and Coordinate Compression with a Fenwick Tree / BIT)

### 4. Line Sweep & Intervals
Processing overlapping events by sorting start times, or iterating backwards to find overlapping bottlenecks.
* Merge Intervals
* Meeting Rooms II (Implemented using a custom from-scratch Min-Heap)
* Car Fleet (Reverse-iteration bottleneck physics)

### 5. Linked Lists
Navigating memory without backwards iteration.
* Insertion Sort List (Pointer manipulation using dummy nodes)

## 🛠️ Tech Stack
* **Language:** C
* **Focus:** $O(1)$ Space Complexity optimizations, In-place modifications, Pointer arithmetic, Custom Data Structures (Min-Heaps, Fenwick Trees).

## 🚀 How to Run
All files are standard C source files with zero external dependencies. To compile and run any of them using GCC:
```bash
gcc filename.c -o output
./output
