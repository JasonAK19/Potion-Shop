#include "Game.h"
#include "Ingredient.h"
#include "Shop.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

Game ::Game() {}

void Game::LoadIngredients() {
    ifstream newFile;

    //String represent different variables of the Ingredient constructor
    string name;
    string ingType;
    string ing1;
    string ing2;

    int ingQuantity = 0;
    int counter = 0;

    newFile.open(PROJ2_DATA);
    if(newFile.is_open()){
        cout << PROJ2_SIZE <<" ingredients loaded" << endl;

       // uses delimiter to split each word in the lines of the text file
        while( getline(newFile,name,',') and getline(newFile,ingType,',') and getline(newFile,ing1,',') and
        getline(newFile,ing2) )
        {
            //Adds a new Ingredient object to each index of the m_ingredients array
            m_ingredients[counter] = Ingredient(name,ingType,ing1,ing2, ingQuantity);
            counter ++;
         }
    }
    else if(!newFile.is_open())
    {
        cout << "Ingredients not loaded " << endl;
    }

    newFile.close();
}

void Game::StartGame() {
    GameTitle();
    LoadIngredients();

    string name;


    cout << "What is the name of your shop" << endl;
    getline(cin, name);
    m_myShop = Shop(name);

    cout << "What would you like to do in " << name <<"'s Shop" << endl;
}

void Game::DisplayIngredients() {
    // this first portion of the function was made to fix an error that would stop the program if there were no known ingredients
    int bugCheck = 0;

    for(int j = 0; j < PROJ2_SIZE; j++){
        if (m_myShop.GetIngredient(j).m_name.empty()){
            bugCheck++;
        }
    }

    if(bugCheck == PROJ2_SIZE){
        cout << "no known ingredients" << endl;
    }

    if (bugCheck != PROJ2_SIZE) {
        for (int i = 0; i <
                        PROJ2_SIZE; i++) {            //This second statement checks for garbage values since the declared size of the array is 32
            if (m_myShop.GetIngredient(i).m_quantity > 0 and !m_myShop.GetIngredient(i).m_type.empty()) {
                cout << i + 1 << ": " << m_myShop.GetIngredient(i).m_name << "; amount owned: " << m_myShop.GetIngredient(i).m_quantity << endl;
            }
        }
    }
}

int Game::MainMenu() {
    int choice;
    bool win = false;

    if(m_myShop.GetRank() == 'S'){
        win = true;

        cout << " YOU WON CONGRATULATIONS!!!!!!!!!!!!!! " << endl;
    }


    if (!win) {
        cout << "what would you like to do in " << m_myShop.GetName() << "'s " << "shop" << endl;
        cout << "1: Display your shop's ingredients" << endl;
        cout << "2: Search for natural ingredients" << endl;
        cout << "3: Attempt to merge ingredients" << endl;
        cout << "4: See score" << endl;
        cout << "5: Quit" << endl;
        cin >> choice;
        m_myShop.CalcRank();

        if(choice == 4){
            m_myShop.ShopScore();
        }

    }
    return choice;
}

void Game::SearchIngredients() {

    srand(time(NULL));
    int counter = 0;
    // the boolean is for when using search and finding ingredient already known to the player
    bool discovered = false;

    Ingredient naturalIngs[PROJ2_SIZE] = {};

    for (int i = 0; i < PROJ2_SIZE; i++){
        if(m_ingredients[i].m_type == "natural"){
            //adds all natural ingredients into their own array
            naturalIngs[i] = m_ingredients[i];
        }
    }

    for(int i = 0; i < PROJ2_SIZE; i++){
        if (!naturalIngs[i].m_type.empty()) {
            counter++;
        }
    }
    // the random number is based on the length of the naturalIngs array so that it can work with any type of text file
    int random = rand() % counter;

    for (int k = 0; k < PROJ2_SIZE; k++) {
        if (naturalIngs[random].m_name == m_myShop.GetIngredient(k).m_name) {
            discovered = true;
        }
    }

    if(!discovered){
        m_myShop.AddIngredient(naturalIngs[random]);
        m_myShop.IncrementQuantity(naturalIngs[random]);
    }
    else {
        m_myShop.IncrementQuantity(naturalIngs[random]);
    }

    cout << "Searching.... ";
    cout << naturalIngs[random].m_name << " found! " << endl;
}

void Game::CombineIngredients() {
    bool canMix = false;
    int check = m_myShop.IngredientCount();

    // for loop is for the event that the player has only one known ingredient but has more than 1 of that ingredient
    for (int i = 0; i < PROJ2_SIZE; i++){
        if(m_myShop.GetIngredient(i).m_quantity >= 2 and (!m_myShop.GetIngredient(i).m_name.empty())){
            canMix = true;
        }
    }

    if (check == 1 and canMix) {
        int x;
        cout << "Which ingredients would you like to merge? " << endl;
        cout << "to list known ingredient enter -1 " << endl;
        cin >> x;
        RequestIngredient(x);
    }
    else if(check < 2){
        cout << "you don't have enough ingredients to combine" << endl;
    }
    else {
        int x;
        cout << "Which ingredients would you like to merge? " << endl;
        cout << "to list known ingredient enter -1 " << endl;
        cin >> x;
        RequestIngredient(x);
    }
}

void Game::RequestIngredient(int &choice) {
    string ing1;
    string ing2;

    //checks if the initial input is -1
    if(choice == -1){
        DisplayIngredients();
    }
    // checks if the input is greater than the total amount of available ingredients
    else if(choice > PROJ2_SIZE){
        choice = -1;
    }
    else {
        choice = m_myShop.CheckIngredient(m_myShop.GetIngredient(choice - 1));
    }

    if(choice != -1) {
        ing1 = m_myShop.GetIngredient(choice).m_name;
    }

    if(choice < -1){
        cout << " No available ingredient " << endl;
    }

    cout << "to list known ingredient enter -1 " << endl;
    cin >> choice;

    if(choice == -1){
        DisplayIngredients();
    }
    else if(choice > PROJ2_SIZE){
        choice = -1;
    }
    else {
        choice = m_myShop.CheckIngredient(m_myShop.GetIngredient(choice - 1));
    }

    if(choice != -1) {
        ing2 = m_myShop.GetIngredient(choice).m_name;
    }

    if(ing1 != " " and ing2 != " "){
        int x = SearchRecipes(ing1,ing2);

        if(x != -1){
            bool discovered = false;

            for (int k = 0; k < PROJ2_SIZE; k++) {
                if (m_ingredients[x].m_name == m_myShop.GetIngredient(k).m_name) {
                    discovered = true;
                }
            }
            if(!discovered){
                m_myShop.AddIngredient(m_ingredients[x]);
                m_myShop.IncrementQuantity(m_ingredients[x]);
            }
            else{
                m_myShop.IncrementQuantity(m_ingredients[x]);
            }

            for(int i = 0; i < PROJ2_SIZE; i++){
                if (m_myShop.GetIngredient(i).m_name == ing1){
                    m_myShop.DecrementQuantity(m_myShop.GetIngredient(i));
                }
            }

            for(int i = 0; i < PROJ2_SIZE; i++){
                if (m_myShop.GetIngredient(i).m_name == ing2){
                    m_myShop.DecrementQuantity(m_myShop.GetIngredient(i));
                }
            }
        }
        else {
            cout << "Attempt to merge failed" << endl;
        }
    }

    else if(choice  == -1){
        DisplayIngredients();
    }
}

int Game::SearchRecipes(string first, string second) {

    for(int i = 0; i < PROJ2_SIZE; i++){
        //checks if both ingredients are part of anothers recipe
        if((first == m_ingredients[i].m_ingredient1 and second == m_ingredients[i].m_ingredient2) or
        (second == m_ingredients[i].m_ingredient1 and first == m_ingredients[i].m_ingredient2)){
            cout << "You combined " << first << " and " << second << " to make " << m_ingredients[i].m_name << endl;
            return i;
        }
    }

    return -1;
}

