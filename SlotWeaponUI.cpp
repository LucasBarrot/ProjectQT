#include "SlotWeaponUI.h"

#include "Game.h"

extern Game * game;

SlotWeaponUI::SlotWeaponUI(int argIndexWeapon, double argSize){
    witchWeapon = argIndexWeapon;

    //set image
    QImage img;

    //choose witch slot is for
    if(witchWeapon == 1){
        img = QImage(game->inventory->get_Weapon_1()->get_pathImgWeapon());
    }
    //set the scale of the image
    double scale = argSize / img.width();
    img = img.scaled(img.width() * scale, img.height() * scale);
    //print the image
    setPixmap(QPixmap::fromImage(img));
}

void SlotWeaponUI::resize(double argSize){
    QImage img;

    //choose witch slot is for
    if(witchWeapon == 1){
        img = QImage(game->inventory->get_Weapon_1()->get_pathImgWeapon());
    }
    //set the scale of the image
    double scale = argSize / img.width();
    img = img.scaled(img.width() * scale, img.height() * scale);
    //print the image
    setPixmap(QPixmap::fromImage(img));
}
