//
// Created by user on 01.03.2026.
//

#ifndef LAB5_MONSTERA_H
#define LAB5_MONSTERA_H
#include "BaseMonster.h"

class MonsterA : public BaseMonster{
public:
    void attack() override;
    void move() override;
    void attackNoPolymorphism();
    void moveNoPolymorphism();
    ~MonsterA();
};


#endif //LAB5_MONSTERA_H
