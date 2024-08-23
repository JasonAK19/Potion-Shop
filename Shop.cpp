#include "Shop.h"
#include "Game.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

Shop::Shop() {

    m_shopName = "Test";
    m_numIngredients = 0;
    m_shopRank = 'F';
}

Shop::Shop(std::string name) {
    m_shopName = name;
    m_numIngredients = 0;
    m_shopRank = 'F';

}

string Shop::GetName() {
    return m_shopName;
}

void Shop::SetName(std::string name) {
    m_shopName = name;
}

int Shop::CheckIngredient(Ingredient ing) {
    if(ing.m_quantity >= 1){
        for(int i = 0; i < PROJ2_SIZE; i++){
            if(m_myIngredients[i].m_name == ing.m_name){
                return i;
            }
        }
    }
    return -1;
}

void Shop::AddIngredient(Ingredient Ingredient) {
    m_myIngredients[m_numIngredients] = Ingredient;
    m_numIngredients++;
}

void Shop::IncrementQuantity(Ingredient Ingredient) {

    cout << Ingredient.m_name << endl;
    cout << Ingredient.m_quantity << endl;

     for (int i = 0; i < PROJ2_SIZE; i++) {
         if(m_myIngredients[i].m_name == Ingredient.m_name)
         m_myIngredients[i].m_quantity += 1;

     }
}

bool Shop::DecrementQuantity(Ingredient Ingredient) {
    if (Ingredient.m_quantity >= 1){

    for (int i = 0; i < PROJ2_SIZE; i++){
        if(m_myIngredients[i].m_name == Ingredient.m_name){
            m_myIngredients[i].m_quantity --;
            return true;
        }
    }
    }
    else{
        return false;
    }
}

bool Shop::CheckQuantity(Ingredient ing1, Ingredient ing2) {
    for(int i =0; i < PROJ2_SIZE; i++) {
        if (ing1.m_quantity >= 1 and ing2.m_quantity >= 1) {
            return true;
        } else {
            return false;
        }
    }
}


Ingredient Shop::GetIngredient(int x) {      //
    if(m_myIngredients[x].m_quantity >= 0 or m_myIngredients[x].m_type.empty()) {
        return m_myIngredients[x];
    }

}

void Shop::CalcRank() {

    int a = IngredientCount();

    if (a >= 1) {

        double rankCheck = (double(a) / PROJ2_SIZE) * 100;

        if (rankCheck >= 100.00) {
            m_shopRank = 'S';
        } else if (rankCheck >= 90 and rankCheck <= 99) {
            m_shopRank = 'A';
        } else if (rankCheck >= 70 and rankCheck <= 89) {
            m_shopRank = 'B';
        } else if (rankCheck >= 50 and rankCheck <= 69) {
            m_shopRank = 'C';
        } else if (rankCheck >= 30 and rankCheck <= 49) {
            m_shopRank = 'D';
        } else if (rankCheck <= 29) {
            m_shopRank = 'F';
        }

    }
}


char Shop::GetRank() {
    return m_shopRank;
}
int Shop::IngredientCount() {
    int count = 0;

    for(int i = 0; i < PROJ2_SIZE; i++){
        if ((!m_myIngredients[i].m_type.empty()) and m_myIngredients[i].m_quantity > 0){
            count++;
        }
    }


    return count;
}

void Shop::ShopScore(){

    int a = IngredientCount();
    double rankCheck = (double(a) / PROJ2_SIZE) * 100;

    if (m_myIngredients  != NULL) {
        cout << "Shop Name: " << m_shopName << endl;
        cout << "Current Rank: " << m_shopRank << endl;

        //Not required for the function but makes it easier to keep track of rank and progression
        cout << "Rank Progress: " << rankCheck << endl;

        cout << "Current Known Ingredients: "<< m_numIngredients << endl;
    }
}

