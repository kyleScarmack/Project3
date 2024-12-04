#include "Parser.h"
#include "Car.h"
#include "Kyle.h"
#include "Brock.h"
#include "map.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "map.hpp"


// function to read a csv file and populate the cars array
int Parser::readCSV(const string& fileName, Car cars[]) {
    ifstream file(fileName);
    string line;
    int count = 0;

    // check if the file can be opened
    if (!file.is_open()) {
        cerr << "Could not open file." << endl;
        return 0;
    }

    // skip the header line
    getline(file, line);

    // read each line and add the car to the array
    while (getline(file, line)) {
        cars[count] = Car::addCar(line);
        count++;
    }

    file.close();

    return count;
}

// main function to handle user input and perform actions
void Parser::parseInput() {
    // create an array to store cars
    Car* cars = new Car[100000];

    // load cars from the csv file
    int numCars = readCSV("Car_data.csv", cars);

    // welcome message
    cout << "Hello and welcome to Orange and Blue Auto!" << endl;
    cout << endl;

    int input = 0;

    // loop until the user chooses to quit
    while (input != 4) {
        // display menu options
        cout << "Choose a search method: " << endl;
        cout << "1. Merge Sort (Search by ID)" << endl;
        cout << "2. Min Heap (Search for Closest Fit Car)" << endl;
        cout << "3. Map (Implemented with Red-Black Tree)" << endl;
        cout << "4. Quit" << endl;

        cout << endl;
        cout << "Enter your choice (1-4): ";
        cin >> input;
        cout << endl;

        // main control switch block
        switch (input) {
            // case 1, merge sort
            case 1: {
                // perform merge sort on cars
                cout << "Sorting cars using merge sort..." << endl;

                auto mergeSortStartTime = chrono::high_resolution_clock::now();

                Kyle kyle;
                kyle.mergeSort(cars, 0, numCars - 1);

                auto mergeSortEndTime = chrono::high_resolution_clock::now();
                chrono::duration<double> mergeSortElapsedTime = mergeSortEndTime - mergeSortStartTime;

                // display the time taken to sort
                cout << "Cars sorted successfully!" << endl;
                cout << "Time taken to merge sort: " << mergeSortElapsedTime.count() << " seconds" << endl;

                // prompt for car id to search
                cout << endl;
                cout << "Enter the car ID to search: ";
                int searchID;
                cin >> searchID;
                cout << endl;

                // check if the id is valid and display the car
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

            // case 2, min heap
            case 2: {
                // start timer for heap construction
                auto heapBuildStartTime = std::chrono::high_resolution_clock::now();

                // declare heap and car objects
                MinHeap heap;
                Car inputCar;

                // updated initial for loop to init heap
                for (int i = 0; i < numCars; ++i) {
                    float score = calculateCloseness(inputCar, cars[i]);
                    heap.push(score, cars[i]);
                }

                // calc time for heap build
                auto heapBuildEndTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> heapBuildElapsedTime = heapBuildEndTime - heapBuildStartTime;

                // display heap build success message
                std::cout << "Heap built successfully!\n";
                std::cout << "Time taken to build heap: " << heapBuildElapsedTime.count() << " seconds\n";

                // collect and validate user inputs for car preferences
                bool validBrand = false;

                // prompt for brand and validate
                do {
                    std::cout << "Enter Brand (Volvo, Honda, Ford, etc): ";
                    std::cin.ignore();
                    std::getline(std::cin, inputCar.brand);

                    validBrand = false;
                    for (int i = 0; i < numCars; ++i) {
                        if (cars[i].brand == inputCar.brand) {
                            validBrand = true;
                            break;
                        }
                    }

                    if (!validBrand) {
                        std::cout << "Invalid brand. Please try again.\n";
                    }
                } while (!validBrand);

                // prompt for model and validate
                bool validModel = false;
                do {
                    std::cout << "Enter Model (Generic Model #1-3, Pilot, Mustang, etc): ";
                    std::getline(std::cin, inputCar.model);

                    validModel = false;
                    for (int i = 0; i < numCars; ++i) {
                        if (cars[i].brand == inputCar.brand && cars[i].model == inputCar.model) {
                            validModel = true;
                            break;
                        }
                    }

                    if (!validModel) {
                        std::cout << "No such car exists for the given brand and model combination. Please try again.\n";
                    }
                } while (!validModel);

                // validate year
                do {
                    std::cout << "Enter Year (1990 - 2022): ";
                    std::cin >> inputCar.year;
                    if (inputCar.year < 1990 || inputCar.year > 2022) {
                        std::cout << "Invalid year. Please enter a value between 1990 and 2022.\n";
                    }
                } while (inputCar.year < 1990 || inputCar.year > 2022);

                // prompt for color
                std::cout << "Enter Color (White, Blue, etc): ";
                std::cin.ignore();
                std::getline(std::cin, inputCar.color);

                // validate mileage
                do {
                    std::cout << "Enter Mileage (2 - 199998): ";
                    std::cin >> inputCar.mileage;
                    if (inputCar.mileage < 2 || inputCar.mileage > 199998) {
                        std::cout << "Invalid mileage. Please enter a value between 2 and 199998.\n";
                    }
                } while (inputCar.mileage < 2 || inputCar.mileage > 199998);

                // validate price
                do {
                    std::cout << "Enter Price (5000 - 80000): $";
                    std::cin >> inputCar.price;
                    if (inputCar.price < 5000 || inputCar.price > 80000) {
                        std::cout << "Invalid price. Please enter a value between $5000 and $80000.\n";
                    }
                } while (inputCar.price < 5000 || inputCar.price > 80000);

                // validate condition
                do {
                    std::cout << "Enter Condition (New or Used): ";
                    std::cin.ignore();
                    std::getline(std::cin, inputCar.condition);
                    if (inputCar.condition != "New" && inputCar.condition != "Used") {
                        std::cout << "Invalid condition. Please enter 'New' or 'Used'.\n";
                    }
                } while (inputCar.condition != "New" && inputCar.condition != "Used");

                // start timer for finding closest car
                auto start = std::chrono::high_resolution_clock::now();

                // rebuild heap using user preferences
                for (int i = 0; i < numCars; ++i) {
                    float score = calculateCloseness(inputCar, cars[i]); // calculate closeness
                    heap.push(score, cars[i]); // add to heap
                }

                // retrieve the closest car
                Car closestCar = heap.pop();

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;

                // display closest car
                std::cout << "\nHere is the closest car to your preferences!\n";
                std::cout << "----------------------------------------\n";
                closestCar.printCar();
                std::cout << "----------------------------------------\n";
                std::cout << "Execution time: " << elapsed.count() << " seconds\n";
                break;
            }
            // case 3, map
            case 3: {

                // menu to select search category
                std::cout << "Select a category to search by: \n";
                std::cout << "1. ID \n";
                std::cout << "2. Brand \n";
                std::cout << "3. Model \n";
                std::cout << "4. Year \n";
                std::cout << "5. Color \n";
                std::cout << "6. Mileage \n";
                std::cout << "7. Price \n";
                std::cout << "8. Condition \n";

                // user input for menu
                int choice;
                std::cout << "\nEnter your choice (1-8): ";
                std::cin >> choice;

                // 1, search by ID
                if (choice == 1) {
                    std::cout << "Enter the car ID to search: ";
                    int searchID;
                    std::cin >> searchID;

                    // try block to create map and search for car
                    // catch unexpected and input errors
                    try {
                        auto startTime = std::chrono::high_resolution_clock::now();

                        std::cout << "Creating map..." << std::endl;

                        DSA::Map<int, Car> carMap;
                        for (int i = 0; i < numCars; ++i) {
                            carMap.insert(cars[i].id, cars[i]);
                        }

                        std::cout << "Success! Map Created!\n\n";

                        Car foundCar = carMap.at(searchID);
                        auto endTime = std::chrono::high_resolution_clock::now();

                        std::cout << "Car found! Here is your car!\n";
                        std::cout << "----------------------------------------\n";
                        foundCar.printCar();
                        std::cout << "----------------------------------------\n";

                        std::chrono::duration<double> elapsed = endTime - startTime;
                        std::cout << "Search time: " << elapsed.count() << " seconds\n";

                    } catch (const std::out_of_range& e) {
                        std::cout << "Error: Car with ID " << searchID << " not found.\n";
                    } catch (const std::exception& e) {
                        std::cerr << "Unexpected Error: " << e.what() << "\n";
                    }
                }

                // 2, search by brand
                else if (choice == 2) {
                    std::cout << "Enter the Brand to Search: ";

                    std::string searchBrand;
                    std::cin >> searchBrand;
                    int count = 0;

                    // check error handling
                    if (searchBrand.length() > 0)
                        searchBrand[0] = std::toupper(searchBrand[0]);

                    try {
                        int test = std::stoi(searchBrand);
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    } catch (std::invalid_argument& e) {

                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.brand == searchBrand) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second.printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    // limit car print to 10 count
                    if (count == 0)
                        std::cout << "No Cars Match Your Request: " << searchBrand << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }

                // 3, search by model
                else if (choice == 3) {
                    std::cout << "Enter the Model to Search: ";

                    std::string searchModel;
                    std::cin >> searchModel;
                    int count = 0;

                    if (searchModel.length() > 0)
                        searchModel[0] = std::toupper(searchModel[0]);

                    try {
                        int test = std::stoi(searchModel);
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    } catch (std::invalid_argument& e) {

                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.model == searchModel) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second.printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    if (count == 0)
                        std::cout << "No Cars Match Your Request: " << searchModel << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }

                // 4, search by year
                else if (choice == 4) {
                    std::cout << "Enter the Year to Search: ";

                    std::string searchYearString;
                    int searchYear;
                    std::cin >> searchYearString;
                    int count = 0;

                    try {
                        searchYear = std::stoi(searchYearString);
                    }
                    catch (std::invalid_argument& e) {
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.year == searchYear) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second.printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    if (count == 0)
                        std::cout << "No Cars Match Your Request: " << searchYear << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }

                // 5, search by color
                else if (choice == 5) {
                    std::cout << "Enter the Color to Search: ";

                    std::string searchColor;
                    std::cin >> searchColor;
                    int count = 0;

                    if (searchColor.length() > 0)
                        searchColor[0] = std::toupper(searchColor[0]);

                    try {
                        int test = std::stoi(searchColor);
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    } catch (std::invalid_argument& e) {

                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.color == searchColor) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second.printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    if (count == 0)
                        std::cout << "No Cars Match Your Request: " << searchColor << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }

                // 6, search by mileage
                else if (choice == 6) {
                    std::cout << "Enter the Mileage to Search: ";

                    std::string searchMileageString;
                    int searchMileage;
                    std::cin >> searchMileageString;
                    int count = 0;

                    try {
                        searchMileage = std::stoi(searchMileageString);
                    }
                    catch (std::invalid_argument& e) {
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.mileage == searchMileage) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second.printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    if (count == 0)
                        std::cout << "No Cars Match Your Request: " << searchMileage << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }

                // 7, search by price
                else if (choice == 7) {
                    std::cout << "Enter the Price to Search: $";

                    std::string searchPriceString;
                    int searchPrice;
                    std::cin >> searchPriceString;
                    int count = 0;

                    try {
                        searchPrice = std::stoi(searchPriceString);
                    }
                    catch (std::invalid_argument& e) {
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.price == searchPrice) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second  .printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    if (count == 0)
                        std::cout << "No Cars Match Your Request: $" << searchPrice << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }

                // 8, search by condition
                else if (choice == 8) {
                    std::cout << "Enter the Condition to Search (New or Used): ";

                    std::string searchCondition;
                    std::cin >> searchCondition;
                    int count = 0;

                    if (searchCondition.length() > 0)
                        searchCondition[0] = std::toupper(searchCondition[0]);

                    try {
                        int test = std::stoi(searchCondition);
                        std::cout << "Invalid Choice. Please Try Again.\n\n";
                        break;
                    } catch (std::invalid_argument& e) {

                    }

                    auto startTime = std::chrono::high_resolution_clock::now();

                    std::cout << "Creating Map..." << std::endl;

                    DSA::Map<int, Car> carMap;
                    for (int i = 0; i < numCars; ++i) {
                        carMap.insert(cars[i].id, cars[i]);
                    }

                    std::cout << "Success! Map Created!\n\n";

                    DSA::Map<int, Car>::Iterator it;
                    for (it= carMap.begin(); it != carMap.end(); ++it)
                    {
                        if (it->second.condition == searchCondition) {
                            count++;
                            if (count <= 10) {
                                std::cout << "Car found! Here are the details:\n";
                                std::cout << "----------------------------------------\n";
                                it->second.printCar();
                                std::cout << "----------------------------------------\n";
                            }
                        }
                    }

                    if (count == 0)
                        std::cout << "No Cars Match Your Request: " << searchCondition << std::endl;
                    else if (count > 10)
                        std::cout << "Additional Results Not Listed: " << count - 10 << "\n";

                    auto endTime = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> elapsed = endTime - startTime;
                    std::cout << "Search time: " << elapsed.count() << " seconds\n";
                }
                else {
                    std::cout << "Invalid Option. Please Try Again." << std::endl;
                }
                break;
            }

            // exit program
            case 4:
                cout << "Thank you for visiting Orange and Blue Auto! Goodbye!";
                break;

            default:
                // invalid menu choice
                cout << "Invalid choice. Please select a valid option (1-4)." << endl;
        }
        cout << endl;
    }
    // cleanup dynamic memory
    delete[] cars;
}
