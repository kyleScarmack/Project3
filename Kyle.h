#pragma once
#include <iostream>
#include "Car.h"
using namespace std;

struct Kyle {
    void mergeSort(Car arr[], int start, int end);
    void merge(Car arr[], int left, int mid, int right);
    Car* binarySearch(Car arr[], int size, int searchID);
};
