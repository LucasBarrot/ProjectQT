#include "Inventory.h"

#include "Game.h"

#include "ListWeapon.h"

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
            Weapon_1 = argEntity;
            game->player->weapon->entityWeapon = argEntity;
            initializedWeapon_1 = true;
            game->player->weapon->weaponEquipeChange();
        }
        else {
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

