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

std::vector<Car> readCarsFromCSV(const std::string& filePath);
float calculateCloseness(const Car& inputCar, const Car& car);

#endif //PROJECT3_BROCK_H
