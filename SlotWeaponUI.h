#ifndef SLOTWEAPONUI_H
#define SLOTWEAPONUI_H

#include <QGraphicsPixmapItem>

class SlotWeaponUI : public QGraphicsPixmapItem {
public:
    SlotWeaponUI(int witchWeapon, double argSize);

    //resize
    void resize(double argSize);

    //update weapon that is print
    void updateWeaponPrint(double argSize);

private:
    int witchWeapon;
};

#endif // SLOTWEAPONUI_H
