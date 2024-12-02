#include "Brock.h"
#include <stdexcept>
#include <cmath>

// inspired by Aman
// TODO: add slides

// Min-Heap methods
void MinHeap::heapifyUp(int index) {
    while (index > 0 && heap[(index - 1) / 2].first > heap[index].first) {
        std::swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void MinHeap::heapifyDown(int index) {
    int size = heap.size();
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left].first < heap[smallest].first) {
        smallest = left;
    }
    if (right < size && heap[right].first < heap[smallest].first) {
        smallest = right;
    }
    if (smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

float calculateCloseness(const Car& inputCar, const Car& car) {
    const float yearWeight = 0.1f;
    const float mileageWeight = 0.2f;
    const float priceWeight = 0.2f;

    float score = 0.0f;
    score += yearWeight * std::abs(inputCar.year - car.year);
    score += mileageWeight * std::abs(inputCar.mileage - car.mileage);
    score += priceWeight * std::abs(inputCar.price - car.price);

    return score;
}

void MinHeap::push(float score, Car car) {
    heap.push_back({score, car});
    heapifyUp(heap.size() - 1);
}

Car MinHeap::pop() {
    if (heap.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    Car topCar = heap[0].second;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return topCar;
}

bool MinHeap::isEmpty() const {
    return heap.empty();
}