#pragma once
#include <iostream>
#include <vector>
#include "Car.h"
using namespace std;

struct Parser {
    int readCSV(const string& fileName, Car cars[]);
    void parseInput();
};