#include "SlotWeaponUI.h"

#include "Game.h"

extern Game * game;

SlotWeaponUI::SlotWeaponUI(int argIndexWeapon, double argSize){
    witchWeapon = argIndexWeapon;

    //set image
    QImage img;

    //choose witch slot is for
    if(witchWeapon == 1 && game->inventory->get_initializedWeapon_1() == true){
        img = QImage(game->inventory->get_weapon_1()->get_pathImgWeapon());
    }
    else if(witchWeapon == 2 && game->inventory->get_initializedWeapon_2()){
        img = QImage(game->inventory->get_weapon_2()->get_pathImgWeapon());
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
    if(witchWeapon == 1 && game->inventory->get_initializedWeapon_1()){
        img = QImage(game->inventory->get_weapon_1()->get_pathImgWeapon());
    }
    else if(witchWeapon == 2 && game->inventory->get_initializedWeapon_2()){
        img = QImage(game->inventory->get_weapon_2()->get_pathImgWeapon());
    }

    //set the scale of the image
    double scale = argSize / img.width();
    img = img.scaled(img.width() * scale, img.height() * scale);
    //print the image
    setPixmap(QPixmap::fromImage(img));
}

void SlotWeaponUI::updateWeaponPrint(double argSize){
    //set image
    QImage img;

    //choose witch slot is for
    if(witchWeapon == 1 && game->inventory->get_initializedWeapon_1()){
        img = QImage(game->inventory->get_weapon_1()->get_pathImgWeapon());
    }
    else if(witchWeapon == 2 && game->inventory->get_initializedWeapon_2()){
        img = QImage(game->inventory->get_weapon_2()->get_pathImgWeapon());
    }

    //set the scale of the image
    double scale = argSize / img.width();
    img = img.scaled(img.width() * scale, img.height() * scale);
    //print the image
    setPixmap(QPixmap::fromImage(img));
}
