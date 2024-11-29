#include "Parser.h"
#include "Car.h"
#include "Kyle.h"
#include <fstream>
#include <sstream>
#include <string>

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
        case 1:
            cout << "Sorting cars using merge sort..." << endl;

            auto startTime = chrono::high_resolution_clock::now();

            Kyle kyle;
            kyle.mergeSort(cars, 0, numCars - 1);

            auto endTime = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsedTime = endTime - startTime;

            cout << "Cars sorted successfully!" << endl;
            cout << "Time taken: " << elapsedTime.count() << " seconds" << endl;

            cout << endl;
            cout << "Enter the car ID to search: ";

            int searchID;
            cin >> searchID;
            cout << endl;

            Car* foundCar = kyle.binarySearch(cars, numCars, searchID);

            if (foundCar != nullptr) {
                cout << "Car found! Here is your car!" << endl;
                cout << endl;
                cout << "----------------------------------------" << endl;
                foundCar->printCar();
                cout << "----------------------------------------" << endl;
            } else {
                cout << "Car with ID " << searchID << " not found in the dealership." << endl;
            }
            break;
        // case 2:
            // add functions correlating to min/max heap output
        // case 3:
            // add functions correlating to map output

    }
}
