#include "Brock.h"
#include <stdexcept>
#include <cmath>

// inspired by
// Aman's Heaps slides
// Discussion 6 - Heaps & Priority Queues
// and 7.1 Extract Max, Heaps programming quiz
// all of which had heapify examples and extraction

// Min-Heap methods
// heapify up function
void MinHeap::heapifyUp(int index) {
    while (index > 0 && heap[(index - 1) / 2].first > heap[index].first) {
        std::swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

// heapify down function
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

// calculate closeness function with weights being high for
// brand, model, year for priority
// and small weights for mileage and price
float calculateCloseness(const Car& inputCar, const Car& car) {
    // define weights for different attributes
    const float brandMismatchPenalty = 10000.0f;
    const float modelMismatchPenalty = 5000.0f;
    const float yearMismatchPenalty = 1000.0f;
    const float mileageWeight = 0.2f;
    const float priceWeight = 0.2f;

    float score = 0.0f;

    // penalize heavily for mismatches in brand, model, and year
    if (inputCar.brand != car.brand) {
        score += brandMismatchPenalty;
    }
    if (inputCar.model != car.model) {
        score += modelMismatchPenalty;
    }
    score += yearMismatchPenalty * std::abs(inputCar.year - car.year);

    // add smaller penalties for differences in price and mileage
    score += mileageWeight * std::abs(inputCar.mileage - car.mileage);
    score += priceWeight * std::abs(inputCar.price - car.price);

    return score;
}

// push function
void MinHeap::push(float score, Car car) {
    heap.push_back({score, car});
    heapifyUp(heap.size() - 1);
}

// pop function
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
