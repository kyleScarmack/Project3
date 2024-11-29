#include <iostream>
#include <vector>
#include "Car.h"
using namespace std;

struct Parser {
    vector<Car> readCSV(const string& fileName);
    void parseInput();
};