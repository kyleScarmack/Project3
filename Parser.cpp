#include "Parser.h"
#include "Car.h"
#include "Kyle.h"
#include "Brock.h"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>


int Parser::readCSV(const string& fileName, Car cars[]) {
    ifstream file(fileName);
    string line;
    int count = 0;

    if (!file.is_open()) {
        cerr << "Could not open file." << endl;
        return 0;
    }

    getline(file, line);

    while (getline(file, line)) {
        cars[count] = Car::addCar(line);
        count++;
    }

    file.close();

    return count;
}

void Parser::parseInput() {
    Car* cars = new Car[100000];
    int numCars = readCSV("Car_data.csv", cars);

    cout << "Hello and welcome to Orange and Blue Auto!" << endl;
    cout << endl;


    // TODO: add separate search functionality
    // Brand: first brand to pop up in either sorts
    // Price, Mileage: rounded value, closest fit
    // Year: first one that pops up
    // Condition: first pops up
    cout << "Choose a search method: " << endl;
    cout << "1. Merge Sort" << endl;
    cout << "2. Min/Max Heap" << endl;
    cout << "3. Map" << endl;

    cout << endl;
    cout << "Enter your choice (1-3): ";

    int input;
    cin >> input;
    cout << endl;

    switch (input) {
        case 1: {
            cout << "Sorting cars using merge sort..." << endl;

            auto mergeSortStartTime = chrono::high_resolution_clock::now();

            Kyle kyle;
            kyle.mergeSort(cars, 0, numCars - 1);

            auto mergeSortEndTime = chrono::high_resolution_clock::now();
            chrono::duration<double> mergeSortElapsedTime = mergeSortEndTime - mergeSortStartTime;

            cout << "Cars sorted successfully!" << endl;
            cout << "Time taken to merge sort: " << mergeSortElapsedTime.count() << " seconds" << endl;

            cout << endl;
            cout << "Enter the car ID to search: ";
            int searchID;
            cin >> searchID;
            cout << endl;

            if (searchID > 0 && searchID <= numCars) {
                cout << "Car found! Here is your car!" << endl;
                cout << "----------------------------------------" << endl;
                auto searchStartTime = chrono::high_resolution_clock::now();
                Car foundCar = cars[searchID - 1];
                auto searchEndTime = chrono::high_resolution_clock::now();
                chrono::duration<double> searchElapsedTime = searchEndTime - searchStartTime;
                foundCar.printCar();
                cout << "----------------------------------------" << endl;
                cout << "Time taken to access car: " << (searchElapsedTime.count() * 1000000) << " seconds" << endl;
            } else {
                cout << "Car with ID " << searchID << " not found in the dealership." << endl;
            }
            break;
        }
        // case 2, min heap
        case 2: {
            Car inputCar;
            std::cout << "Enter Brand (Volvo, Honda, Ford, etc): "; std::cin.ignore(); std::getline(std::cin, inputCar.brand);
            std::cout << "Enter Model (Generic Model #1-3, Pilot, Mustang, etc): "; std::getline(std::cin, inputCar.model);
            std::cout << "Enter Year (1999, 2005, etc): "; std::cin >> inputCar.year;
            std::cout << "Enter Color (White, Blue, etc): "; std::cin.ignore(); std::getline(std::cin, inputCar.color);
            std::cout << "Enter Mileage (80123, 112908, etc): "; std::cin >> inputCar.mileage;
            std::cout << "Enter Price (12999, 30123, etc): $"; std::cin >> inputCar.price;

            auto start = std::chrono::high_resolution_clock::now();
            MinHeap heap;

            // calculate closeness for all cars and push them into the MinHeap
            for (int i = 0; i < numCars; ++i) {
                float score = calculateCloseness(inputCar, cars[i]);
                heap.push(score, cars[i]);
            }

            Car closestCar = heap.pop();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsed = end - start;

            // print the details of the closest car
            std::cout << "Here is the closest car to your preferences!\n";
            std::cout << "----------------------------------------\n";
            closestCar.printCar();
            std::cout << "----------------------------------------\n";
            std::cout << "Execution time: " << elapsed.count() << " seconds\n";
        }
    }
            // add functions correlating to min/max heap output
        // case 3:
            // add functions correlating to map output

}

