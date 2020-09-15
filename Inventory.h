#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <QGraphicsItem>

#include <EntityWeapon.h>

class Inventory : public QGraphicsRectItem {
public:
    Inventory();

    //weapon 1
    void set_Weapon_1(EntityWeapon * argWeapon);
    EntityWeapon *get_Weapon_1();

    //weapon 2
    void set_weaepon_2(EntityWeapon * argWeapon);
    EntityWeapon *get_weapon_2();

    //change weapon
    void changeWeapon(EntityWeapon * argEntity);

    //add first weapon
    void addFirstWeapon(EntityWeapon * argEntity);
private:
    EntityWeapon * Weapon_1;
    EntityWeapon * Weapon_2;
};

#endif // INVENTAIRE_H
