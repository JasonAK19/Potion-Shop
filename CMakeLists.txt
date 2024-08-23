cmake_minimum_required(VERSION 3.23)
project(PotionShop)

set(CMAKE_CXX_STANDARD 14)

add_executable(PotionShop main.cpp Game.cpp Shop.cpp Game.h Ingredient.h Shop.h)
