#include "Inventory.h"

#include "Game.h"

#include "ListWeapon.h"

extern Game * game;

Inventory::Inventory(){

}

void Inventory::set_Weapon_1(EntityWeapon *argWeapon){
    Weapon_1 = argWeapon;
}

EntityWeapon *Inventory::get_Weapon_1(){
    return Weapon_1;
}

void Inventory::set_weaepon_2(EntityWeapon *argWeapon){
Weapon_2 = argWeapon;
}

EntityWeapon *Inventory::get_weapon_2(){
    return Weapon_2;
}

void Inventory::changeWeapon(EntityWeapon * argEntity){
    if(Weapon_1 == NULL){
        Weapon_1 = argEntity;
        game->player->weapon->entityWeapon = argEntity;
    }
    else if(Weapon_2 == NULL){
        Weapon_2 = argEntity;
    }
    else {
        if(Weapon_1 == game->player->weapon->entityWeapon){
            Weapon_1 = argEntity;
            game->player->weapon->entityWeapon = argEntity;
        }
        else {
            Weapon_2 = argEntity;
            game->player->weapon->entityWeapon = argEntity;
        }
    }

}

void Inventory::addFirstWeapon(EntityWeapon * argEntity){
    Weapon_1 = argEntity;
}

