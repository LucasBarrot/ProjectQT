#include "ListWeapon.h"

#include "ListAttackWeapon.h"

#include <QDebug>

#include "Weapon.h"


ListWeapon::ListWeapon(){
    tabConstructorWeapon.push_back((EntityWeapon *(ListWeapon::*)(Weapon *))&ListWeapon::set_swordBasic);
    tabConstructorWeapon.push_back((EntityWeapon *(ListWeapon::*)(Weapon *))&ListWeapon::set_wizardStaff);
    tabConstructorWeapon.push_back((EntityWeapon *(ListWeapon::*)(Weapon *))&ListWeapon::set_bazooka);
}

int ListWeapon::get_sizeTabConstructeurWeapon(){
    return tabConstructorWeapon.size();
}

EntityWeapon * ListWeapon::get_constructeurOnTab(int argIndex, Weapon * argWeapon){
    return (this->*tabConstructorWeapon.at(argIndex))(argWeapon);
}

EntityWeapon *ListWeapon::set_swordBasic(Weapon *argWeapon){
    EntityWeapon * tmpEntity = new EntityWeapon();

    //set name weapon
    tmpEntity->set_nameWeapon("Sword_basique");

    //set damage per bullet of the weapon
    tmpEntity->set_damage(20);

    //set rate Of Fire simple shoot per second
    tmpEntity->set_rateOfFire(2);

    //set rate of fire special shoot in second
    tmpEntity->set_rateOfFireSpecial(2);

    //set speed projectil
    tmpEntity->set_speedProjectil(100);

    //set scale
    tmpEntity->set_scaleImg(1);

    //set img path weapon
    tmpEntity->set_pathImgWeapon(":/Source/Source/Image/Weapon/Sword_basique.png");

    //set img weapon
    tmpEntity->set_imgWeapon(tmpEntity->get_pathImgWeapon());

    //set img projectil shoot by weapon
    tmpEntity->set_pathImgProjectil(":/Source/Source/Image/projectil/Sword_projectil.png");

    //set point to spawn projectil
    tmpEntity->set_pointSpawnProjecitl(QPointF(tmpEntity->get_imgWeapon().width(), tmpEntity->get_imgWeapon().height()/2));

    //set pos weapon
    tmpEntity->set_posWeapon(QPointF(10,10));
    tmpEntity->set_posWeaponInvert(QPointF(-8, 10));

    //set attack weapon
    argWeapon->set_attack_1(&Weapon::oneShoot);
    argWeapon->set_attack_2(&Weapon::arcShoot);

    return tmpEntity;
}

EntityWeapon * ListWeapon::set_wizardStaff(Weapon * argWeapon){
    EntityWeapon * tmpEntity = new EntityWeapon();

    //set name weapon
    tmpEntity->set_nameWeapon("Wizard_Staff");

    //set damage per bullet of the weapon
    tmpEntity->set_damage(15);

    //set rate Of Fire simple shoot per second
    tmpEntity->set_rateOfFire(30);

    //set rate of fire special shoot in second
    tmpEntity->set_rateOfFireSpecial(2);

    //set speed projectil
    tmpEntity->set_speedProjectil(80);

    //set scale
    tmpEntity->set_scaleImg(0.5);

    //set img path weapon
    tmpEntity->set_pathImgWeapon(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");

    //set img weapon
    tmpEntity->set_imgWeapon(tmpEntity->get_pathImgWeapon());

    //set img projectil shoot by weapon
    tmpEntity->set_pathImgProjectil(":/Source/Source/Image/projectil/Projectil_1.png");

    //set point to spawn projectil
    tmpEntity->set_pointSpawnProjecitl(QPointF(tmpEntity->get_imgWeapon().width(), tmpEntity->get_imgWeapon().height()/2));

    //set pos weapon
    tmpEntity->set_posWeapon(QPointF(8,10));
    tmpEntity->set_posWeaponInvert(QPointF(-3, 10));

    //set attack weapon
    argWeapon->set_attack_1(&Weapon::oneShoot);
    argWeapon->set_attack_2(&Weapon::arcShoot);

    //set explosion
    tmpEntity->set_explosion(5);

    return tmpEntity;
}

EntityWeapon * ListWeapon::set_bazooka(Weapon * argWeapon){
    EntityWeapon * tmpEntity = new EntityWeapon();

    //set name weapon
    tmpEntity->set_nameWeapon("Bazooka");

    //set damage per bullet of the weapon
    tmpEntity->set_damage(40);

    //set rate Of Fire simple shoot per second
    tmpEntity->set_rateOfFire(1);

    //set rate of fire special shoot in second
    tmpEntity->set_rateOfFireSpecial(5);

    //set speed projectil
    tmpEntity->set_speedProjectil(150);

    //set scale
    tmpEntity->set_scaleImg(0.5);

    //set img path weapon
    tmpEntity->set_pathImgWeapon(":/Source/Source/Image/Weapon/Bazooka.png");

    //set img weapon
    tmpEntity->set_imgWeapon(tmpEntity->get_pathImgWeapon());

    //set img projectil shoot by weapon
    tmpEntity->set_pathImgProjectil(":/Source/Source/Image/projectil/Projectil_Bazooka.png");

    //set point to spawn projectil
    tmpEntity->set_pointSpawnProjecitl(QPointF(tmpEntity->get_imgWeapon().width(), tmpEntity->get_imgWeapon().height()/2));

    //set pos weapon
    tmpEntity->set_posWeapon(QPointF(8,15));
    tmpEntity->set_posWeaponInvert(QPointF(-3, 15));

    //set explosion
    tmpEntity->set_explosion(30);

    return tmpEntity;
}
