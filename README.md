# _Orange and Blue Auto_, a Car Recommendation System

The **Orange and Blue Auto** is a C++ project designed to recommend optimal car choices based on various criteria and preferences. Utilizing advanced data structures such as min-heap, map backed by Red-Black Tree, and merge sort, this program efficiently processes car datasets to deliver meaningful insights and recommendations. The project is developed and displayed into a cohesive Command Line Interface, so that any customer can use it, and walk away from Orange and Blue Auto with a car they love!

## Features and Menu Options

The program offers the following menu-driven functionalities:

1. **Load Car Dataset**  
   - Allows the user to load a dataset of cars, including details such as ID, make, model, year,  color, mileage, price, and condition

2. **Sort Cars by Criteria**  
   - Enables sorting the dataset based on the previously stated parameters

3. **Recommend Cars**  
   - Suggests cars based on user-defined preferences, leveraging a min-heap and red-black tree map for efficient filtering

4. **Visualize Data**  
   - Displays cohesive prompts and filtered data through CLI
   -  for an insightful visualization of car relationships.

5. **Exit Program**  
   - Safely exits the application.

Each menu option branches into specific workflows tailored to user input, ensuring seamless navigation and intuitive user experience.

## Project Structure
- Source Code: ```main.cpp  Parser.h  Parser.cpp  Car.h  Car.cpp  Kyle.h  Kyle.cpp  Brock.h  Brock.cpp  map.hpp  map.cpp``` for all core logic and data structure implementations
- Build System ```CMakeLists.txt``` for compilation

## Menu Option Nav
When starting the program, the user it met with the following menu
```
Hello and welcome to Orange and Blue Auto!

Choose a search method:
1. Merge Sort (Search by ID)
2. Min Heap (Search for Closest Fit Car)
3. Map (Implemented with Red-Black Tree)
4. Quit

Enter your choice (1-4):
```

Let's explore the menu options below

1. Merge Sort
- After selecting `1` for Merge Sort, the following message will display
```
Sorting cars using merge sort...
Cars sorted successfully!
Time taken to merge sort: (number of seconds here, about 0.58) seconds

Enter the car ID to search:
```
- Here, the user is able to select the car's ID, which ranges from `1 - 100,000`. Here is an example ID with the number `598`
```

## Authors
- Brock Gilman
- Kyle Scarmack
- Alexander Dalton



