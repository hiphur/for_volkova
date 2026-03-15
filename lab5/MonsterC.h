//
// Created by user on 01.03.2026.
//

#ifndef LAB5_MONSTERC_H
#define LAB5_MONSTERC_H
#include "BaseMonster.h"

class MonsterC : public BaseMonster{
public:
    void attack() override;
    void move() override;
    void attackNoPolymorphism();
    void moveNoPolymorphism();
    ~MonsterC();
};



#endif //LAB5_MONSTERC_H
