#include "Parser.h"
#include "Car.h"
#include "Kyle.h"
#include "Brock.h"
#include "map.hpp"
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


    int input = 0;

    while (input != 4) {
        cout << "Choose a search method: " << endl;
        cout << "1. Merge Sort (Search by ID)" << endl;
        cout << "2. Min Heap (Search for Closest Fit Car)" << endl;
        cout << "3. Map (Implemented with Red-Black Tree)" << endl;
        cout << "4. Quit" << endl;

        cout << endl;
        cout << "Enter your choice (1-4): ";
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
                    cout << "Time taken to find car: " << (searchElapsedTime.count() * 1000000) << " microseconds" << endl;
                } else {
                    cout << "Car with ID " << searchID << " not found!" << endl;
                }
                break;
            }
            case 2: {
                auto heapBuildStartTime = std::chrono::high_resolution_clock::now();

                MinHeap heap;

                for (int i = 0; i < numCars; ++i) {
                    float score = 0.0; // Initialize score to zero; scores will be calculated later
                    heap.push(score, cars[i]);
                }

                auto heapBuildEndTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> heapBuildElapsedTime = heapBuildEndTime - heapBuildStartTime;

                std::cout << "Heap built successfully!" << std::endl;
                std::cout << "Time taken to build heap: " << heapBuildElapsedTime.count() << " seconds\n" << std::endl;

                Car inputCar;
                std::cout << "Enter Brand (Volvo, Honda, Ford, etc): ";
                std::cin.ignore(); // Clear the input buffer
                std::getline(std::cin, inputCar.brand);
                std::cout << "Enter Model (Generic Model #1-3, Pilot, Mustang, etc): ";
                std::getline(std::cin, inputCar.model);
                std::cout << "Enter Year (1999, 2005, etc): ";
                std::cin >> inputCar.year;
                std::cout << "Enter Color (White, Blue, etc): ";
                std::cin.ignore();
                std::getline(std::cin, inputCar.color);
                std::cout << "Enter Mileage (80123, 112908, etc): ";
                std::cin >> inputCar.mileage;
                std::cout << "Enter Price (12999, 30123, etc): $";
                std::cin >> inputCar.price;
                // add new and used
                std::cout << "Enter Condition (New or Used): ";
                std::cin.ignore();
                std::getline(std::cin, inputCar.condition);

                auto start = std::chrono::high_resolution_clock::now();

                for (int i = 0; i < numCars; ++i) {
                    float score = calculateCloseness(inputCar, cars[i]);
                    heap.push(score, cars[i]);
                }

                Car closestCar = heap.pop();
                auto end = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double> elapsed = end - start;

                std::cout << "\nHere is the closest car to your preferences!\n";
                std::cout << "----------------------------------------\n";
                closestCar.printCar();
                std::cout << "----------------------------------------\n";
                std::cout << "Execution time: " << elapsed.count() << " seconds\n";
                break;
            }

//            case 3: {
//                DSA::Map<int, Car> carMap;
//
//                for (int i = 0; i < numCars; ++i) {
//                    carMap.insert(cars[i].id, cars[i]);
//                }
//
//                int searchID;
//                std::cout << "Enter the Car ID to search: ";
//                std::cin >> searchID;
//
//                try {
//                    auto startTime = std::chrono::high_resolution_clock::now();
//                    Car foundCar = carMap.at(searchID);
//                    auto endTime = std::chrono::high_resolution_clock::now();
//
//                    std::cout << "Car found! Here are the details:\n";
//                    std::cout << "----------------------------------------\n";
//                    foundCar.printCar();
//                    std::cout << "----------------------------------------\n";
//
//                    std::chrono::duration<double> elapsed = endTime - startTime;
//                    std::cout << "Search time: " << (elapsed.count() * 1000000) << " microseconds\n";
//
//                } catch (const std::out_of_range& e) {
//                    std::cout << "Error: Car with ID " << searchID << " not found.\n";
//                }
//                break;
//            }
            case 4:
                cout << "Thank you for visiting Orange and Blue Auto! Goodbye!";
                break;
            default:
                cout << "Invalid choice. Please select a valid option (1-4)." << endl;
        }

        cout << endl;
    }

    delete[] cars;
}