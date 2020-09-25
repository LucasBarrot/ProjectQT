#include "Inventory.h"

#include "Game.h"

#include "ListWeapon.h"
#include "WeaponOnGround.h"
#include <QDebug>

extern Game * game;

Inventory::Inventory(){
    initializedWeapon_1 = false;
    initializedWeapon_2 = false;

}

void Inventory::set_weapon_1(EntityWeapon *argWeapon){
    Weapon_1 = argWeapon;
}

EntityWeapon *Inventory::get_weapon_1(){
    return Weapon_1;
}

void Inventory::set_weaepon_2(EntityWeapon *argWeapon){
Weapon_2 = argWeapon;
}

EntityWeapon *Inventory::get_weapon_2(){
    return Weapon_2;
}

void Inventory::changeWeapon(EntityWeapon * argEntity){
    if(initializedWeapon_1 == false){
        Weapon_1 = argEntity;
        game->player->weapon->entityWeapon = argEntity;
        initializedWeapon_1 = true;
        game->player->weapon->weaponEquipeChange();
    }
    else if(initializedWeapon_2 == false){
        Weapon_2 = argEntity;
        initializedWeapon_2 = true;
    }
    else {
        if(Weapon_1 == game->player->weapon->entityWeapon){
            //create a new weapon on ground
            WeaponOnGround * weaponOnGround = new WeaponOnGround(Weapon_1, 16);

            weaponOnGround->setParentItem(game->player->get_roomPlayerIs());

            QPointF posWeaponOnGround = game->player->get_roomPlayerIs()->mapFromItem(game->player->parentItem(), game->player->pos());

            //set pos a little bit above
            weaponOnGround->setPos(posWeaponOnGround.x(), posWeaponOnGround.y() + game->player->playerEntity->get_heightEntity() / 2);

            Weapon_1 = argEntity;
            game->player->weapon->entityWeapon = argEntity;
            initializedWeapon_1 = true;
            game->player->weapon->weaponEquipeChange();
        }
        else {
            //create a new weapon on ground
            WeaponOnGround * weaponOnGround = new WeaponOnGround(Weapon_2, 16);

            weaponOnGround->setParentItem(game->player->get_roomPlayerIs());

            //set the position relative to the rooom of the player^
            QPointF posWeaponOnGround = game->player->get_roomPlayerIs()->mapFromItem(game->player->parentItem(), game->player->pos());

            //set pos a little bit aboce
            weaponOnGround->setPos(posWeaponOnGround.x(), posWeaponOnGround.y() + game->player->playerEntity->get_heightEntity() / 2);

            Weapon_2 = argEntity;
            game->player->weapon->entityWeapon = argEntity;
            initializedWeapon_2 = true;
            game->player->weapon->weaponEquipeChange();
        }
    }
    game->ui->updateWeaponSlot();
}

bool Inventory::get_initializedWeapon_1(){
    return initializedWeapon_1;
}

bool Inventory::get_initializedWeapon_2(){
    return initializedWeapon_2;
}

void Inventory::addFirstWeapon(EntityWeapon * argEntity){
    initializedWeapon_1 = true;
    Weapon_1 = argEntity;

}

