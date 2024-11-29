#include "Parser.h"
#include "Car.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Function to read and parse the CSV file
vector<Car> Parser::readCSV(const string& fileName) {
    vector<Car> cars;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cerr << "Could not open file." << endl;
        return cars;
    }

    // Skip the header line
    getline(file, line);

    // Read and parse each line
    while (getline(file, line)) {
        cars.push_back(Car::addCar(line));
    }

    file.close();

    return cars;
}

void Parser::parseInput() {
    cout << "Hello World!" << endl;
    readCSV("Car_data.csv");
}
