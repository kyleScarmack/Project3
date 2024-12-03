#pragma once
#include <iostream>
#include "Car.h"
using namespace std;

// Kyle class for merge sort, sorting by ID
class Kyle {
    void merge(Car arr[], int left, int mid, int right);
public:
    void mergeSort(Car arr[], int start, int end);
};
