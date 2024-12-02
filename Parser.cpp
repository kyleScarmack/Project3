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
            // print case 2 selection (minheap)
            cout << "Using MinHeap to search by ID..." << endl;

            // declare minheap object
            MinHeap minHeap;

            // measure time to build the heap
            auto buildStartTime = chrono::high_resolution_clock::now();
            for (int i = 0; i < numCars; i++) {
                minHeap.insert(cars[i]);
            }
            auto buildEndTime = chrono::high_resolution_clock::now();
            chrono::duration<double> buildTime = buildEndTime - buildStartTime;

            // print build, time, followed by enter ID
            cout << "MinHeap built successfully!" << endl;
            cout << "Time taken to build the heap: " << buildTime.count() << " seconds" << endl;
            cout << endl;
            // pick num 1-100,000
            cout << "Pick number 1 - 100,000 !!!" << endl;
            cout << "Enter the car ID to search: ";

            // get ID input
            int searchID;
            cin >> searchID;
            cout << endl;

            // declare car object
            Car foundCar;

            // measure time to search in the heap
            // added repetitions to record average for more accurate search
            // can remove though
            int repetitions = 1000;
            auto searchStartTime = chrono::high_resolution_clock::now();
            for (int i = 0; i < repetitions; i++) {
                minHeap.searchByID(searchID, foundCar);
            }
            auto searchEndTime = chrono::high_resolution_clock::now();
            chrono::duration<double, std::micro> searchTime = searchEndTime - searchStartTime;

            // take average, in microseconds for increased readability
            double averageSearchTime = searchTime.count() / repetitions;

            if (minHeap.searchByID(searchID, foundCar)) {
                cout << "Car found! Here is your car:" << endl;
                cout << "----------------------------------------" << endl;
                foundCar.printCar();
                cout << "----------------------------------------" << endl;
            } else {
                cout << "Car with ID " << searchID << " not found in the dealership." << endl;
            }

            cout << "Average time taken to search: " << averageSearchTime << " microseconds" << endl;

            break;
        }

        default:
            cout << "Invalid input. Please choose a valid option." << endl;
    }
            // add functions correlating to min/max heap output
        // case 3:
            // add functions correlating to map output

}

