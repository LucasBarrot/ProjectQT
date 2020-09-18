#ifndef LISTENEMY_H
#define LISTENEMY_H

#include "EntityCaracter.h"
#include "Enemy.h"

class ListEnemy {
public:
    ListEnemy();

    //get one function of the tab with is index
    EntityCaracter * get_constructeurOnTab(int argIndex, Enemy * argEnemy);

    int get_sizeTabConstructeurEnemy();

private:

    //list of all function that construct entity weapon
    QVector<EntityCaracter *(ListEnemy::*)(Enemy*)> tabConstructorEnemy;


    //set a entity necromancer
    EntityCaracter * set_necromancer(Enemy * argEnemy);


};


#endif // LISTENEMY_H
