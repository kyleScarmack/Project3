#ifndef PROJECT3_BROCK_H
#define PROJECT3_BROCK_H
#pragma once
#include "Car.h"
#include <vector>
using namespace std;

// Min-Heap class for closeness calculation
class MinHeap {
private:
    std::vector<std::pair<float, Car>> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(float score, Car car);
    Car pop();
    bool isEmpty() const;
};

// Function prototypes
void mergeSort(std::vector<Car>& cars, int left, int right);
void merge(std::vector<Car>& cars, int left, int mid, int right);

std::vector<Car> readCarsFromCSV(const std::string& filePath);
float calculateCloseness(const Car& inputCar, const Car& car);

#endif //PROJECT3_BROCK_H
