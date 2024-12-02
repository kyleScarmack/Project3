#ifndef PROJECT3_BROCK_H
#define PROJECT3_BROCK_H
#pragma once
#include "Car.h"
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<Car> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap() = default;
    void insert(const Car& car);
    Car extractMin();
    bool isEmpty() const;
    bool searchByID(int id, Car& foundCar) const;
};

#endif //PROJECT3_BROCK_H
