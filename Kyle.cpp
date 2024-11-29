#include "Kyle.h"
#include "Car.h"
using namespace std;

// Code inspired by Professor Kapoor's Module 6 Sorting PowerPoint Slides 88-90
void Kyle::mergeSort(Car arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void Kyle::merge(Car arr[], int left, int mid, int right) {
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

    int i = 0, j = 0, k = left;

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

Car* Kyle::binarySearch(Car arr[], int size, int searchID) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].id == searchID) {
            return &arr[mid];
        } else if (arr[mid].id < searchID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nullptr;
}