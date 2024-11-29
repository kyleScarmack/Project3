#include "Kyle.h"
using namespace std;

// Code inspired by Professor Kapoor's Module 6 Sorting PowerPoint Slides 88-90
void Kyle::mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted subarrays
        merge(arr, left, mid, right);
    }
}

void Kyle::merge(int arr[], int left, int mid, int right) {
    // Create X <- arr[left..mid] & Y <- arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int X[n1], Y[n2];

    for (int i = 0; i < n1; i++) {
        X[i] = arr[left + 1];
    }
    for (int j = 0; j < n2; j++) {
        Y[j] = arr[mid + 1 + j];
    }

    // Merge the arrays X and Y into arr
    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (X[i] <= Y[j])
        {
            arr[k] = X[i];
            i++;
        } else {
            arr[k] = Y[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either X or Y append the remaining elements
    while (i < n1) {
        arr[k] = X[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = Y[j];
        j++;
        k++;
    }
}
