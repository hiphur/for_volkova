//
// Created by user on 01.03.2026.
//

#ifndef LAB5_BASEMONSTER_H
#define LAB5_BASEMONSTER_H


class BaseMonster{
public:
    virtual void attack();
    virtual void move();
    void attackNoPolymorphism();
    void moveNoPolymorphism();

    virtual ~BaseMonster();
};


#endif //LAB5_BASEMONSTER_H
