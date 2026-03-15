//
// Created by user on 01.03.2026.
//

#include "MonsterB.h"
#include <iostream>
void MonsterB::attack() {
    std::cout << "MonsterB uses virtual attack()" << std::endl;
}
void MonsterB::move() {
    std::cout << "MonsterB uses virtual move()" << std::endl;
}
void MonsterB::attackNoPolymorphism() {
    std::cout << "MonsterB uses attackNoPolymorphism()" << std::endl;

}
void MonsterB::moveNoPolymorphism() {
    std::cout << "MonsterB uses moveNoPolymorphism()" << std::endl;
}
MonsterB::~MonsterB() {

}