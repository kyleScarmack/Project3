#include "Brock.h"
#include <iostream>

// inspired by Aman
// TODO: add slides
void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].id >= heap[parent].id)
            break;
        swap(heap[index], heap[parent]);
        index = parent;
    }
}

void MinHeap::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && heap[leftChild].id < heap[smallest].id)
            smallest = leftChild;
        if (rightChild < size && heap[rightChild].id < heap[smallest].id)
            smallest = rightChild;

        if (smallest == index)
            break;

        swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

void MinHeap::insert(const Car& car) {
    heap.push_back(car);
    heapifyUp(heap.size() - 1);
}

Car MinHeap::extractMin() {
    if (isEmpty()) {
        throw runtime_error("Heap is empty.");
    }

    Car minCar = heap.front();
    heap.front() = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return minCar;
}

bool MinHeap::isEmpty() const {
    return heap.empty();
}

bool MinHeap::searchByID(int id, Car& foundCar) const {
    for (const auto& car : heap) {
        if (car.id == id) {
            foundCar = car;
            return true;
        }
    }
    return false;
}