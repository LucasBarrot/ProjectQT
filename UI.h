#ifndef UI_H
#define UI_H

#include <QGraphicsRectItem>

#include "Minimap.h"
#include "Heart.h"
#include "SlotWeaponUI.h"


class UI : public QGraphicsRectItem {
public:
    UI(double width, double height);
    void printOnScreen();

    //resize
    void resize();

    //update weapon on Ui
    void updateWeaponSlot();

    //update print health after change (damage or heal)
    void updateHealthUI();

    //minimap
    Minimap * minimap;

    //Slot weapon
    SlotWeaponUI * slotWeapon_1;
    SlotWeaponUI * slotWeapon_2;
private:
     QVector<Heart*> tabHeart;
};

#endif // UI_H
