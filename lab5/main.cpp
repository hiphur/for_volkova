#include <iostream>

#include "BaseMonster.h"
#include "MonsterA.h"
#include "MonsterB.h"
#include "MonsterC.h"
int main() {
    const int monsterSize = 3;
    BaseMonster*  monsters[monsterSize] = {new MonsterA, new MonsterB, new MonsterC};

    for(int i = 0; i < monsterSize; i++){
        monsters[i]->attack();
        monsters[i]->move();
    }
    for(int i = 0; i < monsterSize; i++){
        monsters[i]->attackNoPolymorphism();
        monsters[i]->moveNoPolymorphism();
    }

    MonsterA* ma = new MonsterA;
    MonsterB* mb = new MonsterB;
    MonsterC* mc = new MonsterC;
    ma->attackNoPolymorphism();
    ma->moveNoPolymorphism();
    mb->attackNoPolymorphism();
    mb->moveNoPolymorphism();
    mc->attackNoPolymorphism();
    mc->moveNoPolymorphism();

    for(int i = 0; i < monsterSize; i++) {
        delete monsters[i];
    }
    delete ma;
    delete mb;
    delete mc;
    return 0;
    }