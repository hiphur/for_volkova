//
// Created by user on 01.03.2026.
//
#include "BaseMonster.h"
#include <iostream>

void BaseMonster::attack(){
        std::cout << "BaseMonster uses virtual attack()" << std::endl;
}
void BaseMonster::move(){

        std::cout << "Base monster uses virtual move()" << std::endl;
}
void BaseMonster::attackNoPolymorphism(){
    std::cout << "BaseMonster uses attackNoPolymorphism()" << std::endl;
}
void BaseMonster::moveNoPolymorphism(){
        std::cout << "BaseMonster uses moveNoPolymorphism()" << std::endl;
}

BaseMonster::~BaseMonster() {

}
