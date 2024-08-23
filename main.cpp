//Title: Project 2 for Spring 2023
//Author: Jason Appiah-Kubi
//Date: 2/25/2023
//Description: This is main for project 2

#include "Game.h"
#include "Shop.h"
#include "Ingredient.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main() {

	srand(time(NULL));
	Game newGame;

	newGame.StartGame();


   int choice;
    do {
        switch (newGame.MainMenu()) {

            case 1:
                newGame.DisplayIngredients();
                break;
            case 2:
                newGame.SearchIngredients();
                break;
            case 3:
                newGame.CombineIngredients();
                break;
            case 4:
                break;
            case 5:
                cout << endl;
                choice = 5;
                break;
            default:
                cout << "enter a number (1-5)" << endl;
        }
    }
    while(choice != 5);

    return 0;

}
