#ifndef LISTWEAPON_H
#define LISTWEAPON_H

#include "EntityWeapon.h"
#include "Weapon.h"

class ListWeapon {
public:
    ListWeapon();

    //get one function of the tab with is index
    EntityWeapon * get_constructeurOnTab(int argIndex, Weapon * argWeapon);

    int get_sizeTabConstructeurWeapon();

private:

    //list of all function that construct entity weapon
    QVector<EntityWeapon *(ListWeapon::*)(Weapon *)> tabConstructorWeapon;

    //set wizard staff
    EntityWeapon *set_wizardStaff(Weapon * argWeapon);

    //set bazooka
    EntityWeapon *set_bazooka(Weapon * argWeapon);


};

#endif // LISTWEAPON_H
