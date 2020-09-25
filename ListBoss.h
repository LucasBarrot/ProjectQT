#ifndef LISTBOSS_H
#define LISTBOSS_H

#include "EntityCaracter.h"
#include "Enemy.h"

class ListBoss {
public:
    ListBoss();

    //get one function of the tab with is index
    EntityCaracter * get_constructeurOnTab(int argIndex, Enemy * argEnemy);

    int get_sizeTabConstructeurEnemy();

private:

    //list of all function that construct entity weapon
    QVector<EntityCaracter *(ListBoss::*)(Enemy*)> tabConstructorBoss;


    //set a entity big demon
    EntityCaracter * set_bigDemon(Enemy * argEnemy);

    //set spider
    EntityCaracter * set_spider(Enemy * argEnemy);

};

#endif // LISTBOSS_H
