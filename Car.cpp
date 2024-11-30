#include "Car.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

Car Car::addCar(string line) {
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
    car.condition.erase(remove_if(car.condition.begin(), car.condition.end(), ::isspace), car.condition.end());

    return car;
}

void Car::printCar() {
    cout << "ID: " << id << endl;
    cout << "Brand: " << brand << endl;
    cout << "Model: " << model << endl;
    cout << "Year: " << year << endl;
    cout << "Color: " << color << endl;
    cout << "Mileage: " << mileage << " miles" << endl;
    cout << "Price: $" << price << endl;
    cout << "Condition: " << condition << endl;
}
