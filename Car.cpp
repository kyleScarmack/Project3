#include "Car.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Function to parse a single line of the CSV and create a Car object
Car Car::addCar(const string& line) {
    Car car;
    stringstream ss(line);
    string id, year, mileage, price;

    getline(ss, id, ',');
    car.id = stoi(id);

    getline(ss, car.brand, ',');

    getline(ss, car.model, ',');

    getline(ss, year, ',');
    car.year = stoi(year);

    getline(ss, car.color, ',');

    getline(ss, mileage, ',');
    car.mileage = stoi(mileage);

    getline(ss, price, ',');
    car.price = stod(price);

    getline(ss, car.condition, ',');

    return car;
}

void Car::printCar(Car& car) {
    cout << "Here is your car!" << endl;
    cout << "ID: " << car.id << endl;
    cout << "Brand: " << car.brand << endl;
    cout << "Model: " << car.model << endl;
    cout << "Year: " << car.year << endl;
    cout << "Mileage: " << car.mileage << " miles" << endl;
    cout << "Price: $" << car.price << endl;
    cout << "Condition: $" << car.condition << endl;
}
