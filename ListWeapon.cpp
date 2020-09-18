#include "ListWeapon.h"

#include <QDebug>

ListWeapon::ListWeapon(){

    tabConstructorWeapon.push_back((EntityWeapon *(ListWeapon::*)())&ListWeapon::set_wizardStaff);
    tabConstructorWeapon.push_back((EntityWeapon *(ListWeapon::*)())&ListWeapon::set_bazooka);
}

int ListWeapon::get_sizeTabConstructeurWeapon(){
    return tabConstructorWeapon.size();
}

EntityWeapon * ListWeapon::get_constructeurOnTab(int argIndex){
    return (this->*tabConstructorWeapon.at(argIndex))();
}

EntityWeapon * ListWeapon::set_wizardStaff(){
    EntityWeapon * tmpEntity = new EntityWeapon();

    //set name weapon
    tmpEntity->set_nameWeapon("Wizard_Staff");

    //set damage per bullet of the weapon
    tmpEntity->set_damage(15);

    //set rate Of Fire simple shoot per second
    tmpEntity->set_rateOfFire(30);

    //set rate of fire special shoot in second
    tmpEntity->set_rateOfFireSpecial(2);

    //set scale
    tmpEntity->set_scaleImg(0.5);

    //set img weapon
    tmpEntity->set_imgWeapon(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");

    //set img path weapon
    tmpEntity->set_pathImgWeapon(":/Source/Source/Image/Weapon/weapon_red_magic_staff.png");

    //set img projectil shoot by weapon
    tmpEntity->set_pathImgProjectil(":/Source/Source/Image/projectil/Projectil_1.png");

    //set point to spawn projectil
    tmpEntity->set_pointSpawnProjecitl(QPointF(tmpEntity->get_imgWeapon().width(), tmpEntity->get_imgWeapon().height()/2));

    //set pos weapon
    tmpEntity->set_posWeapon(QPointF(8,10));
    tmpEntity->set_posWeaponInvert(QPointF(-3, 10));

    return tmpEntity;
}

EntityWeapon * ListWeapon::set_bazooka(){
    EntityWeapon * tmpEntity = new EntityWeapon();

    //set name weapon
    tmpEntity->set_nameWeapon("Bazooka");

    //set damage per bullet of the weapon
    tmpEntity->set_damage(40);

    //set rate Of Fire simple shoot per second
    tmpEntity->set_rateOfFire(1);

    //set rate of fire special shoot in second
    tmpEntity->set_rateOfFireSpecial(5);

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

    return tmpEntity;
}
