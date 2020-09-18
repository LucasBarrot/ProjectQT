#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <QGraphicsItem>

#include <EntityWeapon.h>

class Inventory : public QGraphicsRectItem {
public:
    Inventory();

    //weapon 1
    void set_weapon_1(EntityWeapon * argWeapon);
    EntityWeapon *get_weapon_1();

    //weapon 2
    void set_weaepon_2(EntityWeapon * argWeapon);
    EntityWeapon *get_weapon_2();

    //change weapon
    void changeWeapon(EntityWeapon * argEntity);

    //get initialized weapon 1 and 2
    bool get_initializedWeapon_1();
    bool get_initializedWeapon_2();


    //add first weapon
    void addFirstWeapon(EntityWeapon * argEntity);
private:
    //set entity weapon of inventory
    EntityWeapon * Weapon_1;
    EntityWeapon * Weapon_2;

    //check if weapon is initialized
    bool initializedWeapon_1;
    bool initializedWeapon_2;
};

#endif // INVENTAIRE_H
