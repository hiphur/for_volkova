//
// Created by user on 01.03.2026.
//

#include "MonsterA.h"
#include <iostream>
void MonsterA::attack() {
    std::cout << "MonsterA uses virtual attack()" << std::endl;
}
void MonsterA::move() {
    std::cout << "MonsterA uses virtual move()" << std::endl;
}
void MonsterA::attackNoPolymorphism() {
    std::cout << "MonsterA uses attackNoPolymorphism()" << std::endl;

}
void MonsterA::moveNoPolymorphism() {
    std::cout << "MonsterA uses moveNoPolymorphism()" << std::endl;
}
MonsterA::~MonsterA() {

}
