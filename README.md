# Potion-Shop

I can analyze the files you have provided to help create a description for the README. Here's a brief overview of what I gathered from the files:

### Potion-Shop

Potion-Shop is a C++ based program that allows users to manage a virtual potion shop. The main functionalities include loading ingredients from a file, searching for natural ingredients, combining ingredients to create new ones, and managing the shop's inventory and rank.

### Key Features
- **Loading Ingredients**: Load ingredients from a file into the game.
- **Searching Ingredients**: Search for natural ingredients and add them to the shop's inventory.
- **Combining Ingredients**: Combine known ingredients to create new ones.
- **Inventory Management**: Display and manage the inventory of ingredients in the shop.
- **Shop Ranking**: Calculate and display the shop’s rank based on the number and type of ingredients known.

### Files
- **Game.cpp & Game.h**: Contains the main game logic, including methods for starting the game, loading ingredients, searching for ingredients, combining ingredients, and managing the main menu.
- **Ingredient.h**: Defines the Ingredient struct used to store data about ingredients.
- **Shop.cpp & Shop.h**: Manages the shop's state, including the name, rank, and inventory of ingredients.
- **CMakeLists.txt**: Configuration file to build the project using CMake.

### Getting Started
1. **Clone the repository**:
    ```sh
    git clone https://github.com/JasonAK19/Potion-Shop.git
    ```
2. **Build the project**:
    ```sh
    cd Potion-Shop
    mkdir build
    cd build
    cmake ..
    make
    ```
3. **Run the program**:
    ```sh
    ./PotionShop
    ```
