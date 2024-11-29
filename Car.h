#pragma once
#include <string>
using namespace std;

struct Car {
    int id;
    string brand;
    string model;
    int year;
    string color;
    int mileage;
    double price;
    string condition;

    static Car addCar(const string& line);
    void printCar(Car& car);
};
