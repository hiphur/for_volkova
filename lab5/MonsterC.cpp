//
// Created by user on 01.03.2026.
//

#include "MonsterC.h"
#include <iostream>
void MonsterC::attack() {
    std::cout << "MonsterC uses virtual attack()" << std::endl;
}
void MonsterC::move() {
    std::cout << "MonsterC uses virtual move()" << std::endl;
}
void MonsterC::attackNoPolymorphism() {
    std::cout << "MonsterC uses attackNoPolymorphism()" << std::endl;

}
void MonsterC::moveNoPolymorphism() {
    std::cout << "MonsterC uses moveNoPolymorphism()" << std::endl;
}
MonsterC::~MonsterC() {

}