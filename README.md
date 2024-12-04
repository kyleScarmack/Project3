# _Orange and Blue Auto_, a Car Recommendation System

The **Orange and Blue Auto** is a C++ project designed to recommend optimal car choices based on various criteria and preferences. Utilizing advanced data structures such as min-heap, map backed by Red-Black Tree, and merge sort, this program efficiently processes car datasets to deliver meaningful insights and recommendations. The project is developed and displayed into a cohesive Command Line Interface, so that any customer can use it, and walk away from Orange and Blue Auto with a car they love!

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

## 1. Merge Sort (Search by ID)
- After selecting `1` for Merge Sort, the following message will
```
Enter your choice (1-4):1

Sorting cars using merge sort...
Cars sorted successfully!
Time taken to merge sort: (number of seconds here) seconds

Enter the car ID to search:
```

- Here, the user is able to select the car's ID, which ranges from `1 - 100,000`. Here is an example ID with the number `598`, followed by the program prompting for a menu choice again
```
Car found! Here is your car!
----------------------------------------
ID: 598
Brand: Subaru
Model: Generic Model 2
Year: 2007
Color: Red
Mileage: 153169 miles
Price: $51728
Condition: New
----------------------------------------
Time taken to find car: (number of microseconds here) microseconds

Choose a search method:
1. Merge Sort (Search by ID)
2. Min Heap (Search for Closest Fit Car)
3. Map (Implemented with Red-Black Tree)
4. Quit

Enter your choice (1-4):
```

## 2. Min Heap (Search for Closest Fit Car)
- After selecting `2` for Min Heap, the following message will display
```
Enter your choice (1-4):2

Heap built successfully!
Time taken to build heap: (number of seconds here) seconds
Enter Brand (Volvo, Honda, Ford, etc):
```

- Here, the user will be able to select filters for the car search sequentially, in the order of `Brand, Model, Year, Color, Mileage, Price, Condition`. Based on the user's input, `Brand, Model, Year` filters are weighted to be the most, while `Mileage, Price, Condition` filters are weighted to be the least in closeness. This is to ensure that _Orange and Blue Auto_ delivers the car best tailored to the customer's needs... if they want a **Honda Pilot** for a certain price with good mileage, we got it!
```
Enter Brand (Volvo, Honda, Ford, etc):Honda

Enter Model (Generic Model #1-3, Pilot, Mustang, etc):Pilot

Enter Year (1990 - 2022):2002

Enter Color (White, Blue, etc):White

Enter Mileage (2 - 199998):80123

Enter Price (5000 - 80000): $12123

Enter Condition (New or Used):New


Here is the closest car to your preferences!
----------------------------------------
ID: 60716
Brand: Honda
Model: Pilot
Year: 2001
Color: Red
Mileage: 78339 miles
Price: $9052
Condition: New
----------------------------------------
Execution time: (number of seconds here) seconds
```

- Let's say the customer isn't that knowledgable on the cars we have in stock, or just on cars in general, we got that covered with awesome error handling on each input. The following is a similar sequence of searching with Min Heap, but with errors accounted for. For example, a _Honda Mustang_ doesn't exist, but a _Honda Pilot_ sure does!
```
Enter Brand (Volvo, Honda, Ford, etc):Honda

Enter Model (Generic Model #1-3, Pilot, Mustang, etc):Mustang

No such car exists for the given brand and model combination. Please try again.
Enter Model (Generic Model #1-3, Pilot, Mustang, etc):Pilot

Enter Year (1990 - 2022):2024

Invalid year. Please enter a value between 1990 and 2022.
Enter Year (1990 - 2022):2002

Enter Color (White, Blue, etc):White

Enter Mileage (2 - 199998):1

Invalid mileage. Please enter a value between 2 and 199998.
Enter Mileage (2 - 199998):80123

Enter Price (5000 - 80000): $4999

Invalid price. Please enter a value between $5000 and $80000.
Enter Price (5000 - 80000): $12123

Enter Condition (New or Used):New


Here is the closest car to your preferences!
----------------------------------------
ID: 60716
Brand: Honda
Model: Pilot
Year: 2001
Color: Red
Mileage: 78339 miles
Price: $9052
Condition: New
----------------------------------------
Execution time: (number of seconds here) seconds
```

## 3. Map (Implemented with Red-Black Tree)
- After selecting `3` for Map, the following message will display
```
Enter your choice (1-4):3

Select a category to search by:
1. ID
2. Brand
3. Model
4. Year
5. Color
6. Mileage
7. Price
8. Condition

Enter your choice (1-8):
```

- Here, the user will be able to search for a specific filter, with `ID` outputting the exact ID similar to Merge Sort
```
Enter your choice (1-8):1

Enter the car ID to search:123

Creating map...
Success! Map created!

Car found! Here is your car!
----------------------------------------
ID: 123
Brand: Audi
Model: Generic Model 3
Year: 1998
Color: Black
Mileage: 47423 miles
Price: $60030
Condition: New
----------------------------------------
Search time: (number of seconds here) seconds
```

- As for the rest of the filters, they output the first **10** instances of said filter that appears on our lot, as well as the count of how many left we have on our lot that isn't displayed
```
Enter your choice (1-8):2

Enter the Brand to Search:Lexus

Creating Map...
Success! Map Created!

Car found! Here are the details:
----------------------------------------
ID: 12
Brand: Lexus
Model: Generic Model 3
Year: 1992
Color: Silver
Mileage: 69360 miles
Price: $76077
Condition: New
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 14
Brand: Lexus
Model: Generic Model 2
Year: 1998
Color: Red
Mileage: 56308 miles
Price: $53734
Condition: Used
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 23
Brand: Lexus
Model: Generic Model 1
Year: 2019
Color: Green
Mileage: 121183 miles
Price: $5430
Condition: Used
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 44
Brand: Lexus
Model: Generic Model 2
Year: 2009
Color: White
Mileage: 172687 miles
Price: $9931
Condition: Used
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 48
Brand: Lexus
Model: Generic Model 1
Year: 1998
Color: Black
Mileage: 20314 miles
Price: $23095
Condition: New
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 70
Brand: Lexus
Model: Generic Model 3
Year: 2001
Color: White
Mileage: 86800 miles
Price: $56282
Condition: New
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 89
Brand: Lexus
Model: Generic Model 3
Year: 2004
Color: Green
Mileage: 21611 miles
Price: $71571
Condition: Used
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 127
Brand: Lexus
Model: Generic Model 3
Year: 1999
Color: Blue
Mileage: 192485 miles
Price: $35885
Condition: Used
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 128
Brand: Lexus
Model: Generic Model 1
Year: 2014
Color: White
Mileage: 136972 miles
Price: $73946
Condition: Used
----------------------------------------
Car found! Here are the details:
----------------------------------------
ID: 156
Brand: Lexus
Model: Generic Model 3
Year: 2001
Color: Silver
Mileage: 16091 miles
Price: $67174
Condition: New
----------------------------------------
Additional Results Not Listed: 5115
Search time: (number of seconds here) seconds
```

## 4. Quit
- Here, the user also has the ability to quit the program whenever once they are satisfied with the car they're going home with!
```
Choose a search method:
1. Merge Sort (Search by ID)
2. Min Heap (Search for Closest Fit Car)
3. Map (Implemented with Red-Black Tree)
4. Quit

Enter your choice (1-4):4


Thank you for visiting Orange and Blue Auto! Goodbye!
```

## Authors
- Brock Gilman
- Kyle Scarmack
- Alexander Dalton

## YouTube Demonstration
- Here is the link to a demonstration of our code and menu navigation: 
https://www.youtube.com/watch?v=f7QEjl7dumI

