#include "Chest.h"

#include <random>

#include "Game.h"
#include "ListWeapon.h"
#include "WeaponOnGround.h"

extern Game * game;

Chest::Chest(){
    //set path to open chest and close chest
    pathChestClose = ":/Source/Source/Image/Chest/chest_full_open_anim_f0.png";
    pathChestOpen = ":/Source/Source/Image/Chest/chest_full_open_anim_f2.png";

    //set pixmap to close chest
    QImage img(pathChestClose);
    setPixmap(QPixmap::fromImage(img));

    //set chest open to false because is close
    chestOpen = false;
}

//return if the chest is already open
bool Chest::get_chestOpen(){
    return chestOpen;
}

void Chest::openChest(){
    //open the chest only if it close
    if(!chestOpen){
        //change the value to be true because now the chest gonna be open
        chestOpen = true;
        //set pixmap to open chest
        QImage img(pathChestOpen);
        setPixmap(QPixmap::fromImage(img));

        //spawn a random weapon of listWeapon
        int indexRandWeapon = rand() % game->listWeapon->get_sizeTabConstructeurWeapon();

        //get the entity from the list of constructeur weapon
        EntityWeapon * entityWeapon = game->listWeapon->get_constructeurOnTab(indexRandWeapon, game->player->weapon);

        //create a new weapon on ground
        WeaponOnGround * weaponOnGround = new WeaponOnGround(entityWeapon, img.width());

        weaponOnGround->setParentItem(this);

        //set pos a little bit aboce
        weaponOnGround->setPos(0, -5);
    }

}
