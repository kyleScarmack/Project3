#include "Car.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

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
    car.price = stoi(price);

    getline(ss, car.condition, ',');

    return car;
}

void Car::printCar() {
    cout << "ID: " << id << endl;
    cout << "Brand: " << brand << endl;
    cout << "Model: " << model << endl;
    cout << "Year: " << year << endl;
    cout << "Mileage: " << mileage << " miles" << endl;
    cout << "Price: $" << price << endl;
    cout << "Condition: " << condition;
}
