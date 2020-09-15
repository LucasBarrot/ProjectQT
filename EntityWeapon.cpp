#include "EntityWeapon.h"

#include "Game.h"

extern Game * game;

EntityWeapon::EntityWeapon(){
    //define defautl value
    nameWeapon = "";
    damage = 0;
    rateOfFirePerSeconde = 0;
    rateOfFireSpecial = 0;
    angleAiming = 0;
    specialShootReady = true;
    simpleShootReady = true;
}

void EntityWeapon::set_nameWeapon(QString argName){
    nameWeapon = argName;
}

QString EntityWeapon::get_nameWeapon(){
    return nameWeapon;
}

void EntityWeapon::set_damage(double argDamage){
    damage = argDamage;
}

double EntityWeapon::get_damage(){
    return damage;
}

void EntityWeapon::set_rateOfFire(double argRateOfFire){
    rateOfFirePerSeconde = argRateOfFire;
}

double EntityWeapon::get_rateOfFire(){
    return rateOfFirePerSeconde;
}

void EntityWeapon::set_rateOfFireSpecial(double argTime){
    rateOfFireSpecial = argTime;
}

void EntityWeapon::set_imgWeapon(QString argPath){
    //set image of the weapon
    img = QImage(argPath);
    img = img.scaled(10, 4);
    setPixmap(QPixmap::fromImage(img));
}

QImage EntityWeapon::get_imgWeapon(){
    return img;
}

void EntityWeapon::set_pathImgWeapon(QString argPath){
    pathImgWeapon = argPath;
}

QString EntityWeapon::get_pathImgWeapon(){
    return pathImgWeapon;
}

void EntityWeapon::set_pathImgProjectil(QString argPath){
    pathImgrojectil = argPath;
}

QString EntityWeapon::get_pathImgProjectil(){
    return pathImgrojectil;
}

void EntityWeapon::set_angleWeapon(double argAngle){
    angleAiming = argAngle;
}

double EntityWeapon::get_angleWeapon(){
    return angleAiming;
}

void EntityWeapon::set_posWeapon(QPointF argPos){
    posWeapon = argPos;
}

QPointF EntityWeapon::get_posWeapon(){
    return posWeapon;
}

void EntityWeapon::set_posWeaponInvert(QPointF argPos){
    posWeaponInvert = argPos;
}

QPointF EntityWeapon::get_posWeaponInvert(){
    return posWeaponInvert;
}

void EntityWeapon::updateSimpleShoot(bool argReady){
    simpleShootReady = argReady;
}

void EntityWeapon::updateSpecialShoot(bool argReady){
    specialShootReady = argReady;
}

bool EntityWeapon::get_simpleShootReady(){
    return simpleShootReady;
}

bool EntityWeapon::get_specialShootReady(){
    return specialShootReady;
}


void EntityWeapon::turnWeapon(bool invert)
{

}
