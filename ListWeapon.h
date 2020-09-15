#ifndef LISTWEAPON_H
#define LISTWEAPON_H

#include "EntityWeapon.h"

class ListWeapon {
public:
    ListWeapon();

    //get one function of the tab with is index
    EntityWeapon * get_constructeur(int argIndex);

private:

    //list of all function that construct entity weapon
    QVector<EntityWeapon *(ListWeapon::*)()> tabConstructorWeapon;

    //set wizard staff
    EntityWeapon *set_wizardStaff();

    //set bazooka
    EntityWeapon *set_bazooka();


};

#endif // LISTWEAPON_H
