#include "Kyle.h"
#include "Car.h"
using namespace std;

// Code inspired by Professor Kapoor's Module 6 Sorting PowerPoint Slides 88-90
void Kyle::mergeSort(Car arr[], int left, int right) {
    // Base case is left (start) = right (end) and sorting an array of 1
    if (left < right) {

        // Mid is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted subarrays
        merge(arr, left, mid, right);
    }
}

// Code inspired by Professor Kapoor's Module 6 Sorting PowerPoint Slides 88-90
// Merge two subarrays from arr
void Kyle::merge(Car arr[], int left, int mid, int right) {
    // Create L <- arr[left..mid] & R <- arr[mid + 1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Car* L = new Car[n1];
    Car* R = new Car[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Merge the arrays L and R into arr
    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i].id <= R[j].id) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or R append the remaining elements
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}