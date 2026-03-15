//
// Created by user on 01.03.2026.
//

#ifndef LAB5_MONSTERB_H
#define LAB5_MONSTERB_H
#include "BaseMonster.h"

class MonsterB : public BaseMonster{
public:
    void attack() override;
    void move() override;
    void attackNoPolymorphism();
    void moveNoPolymorphism();
    ~MonsterB();
};


#endif //LAB5_MONSTERB_H
