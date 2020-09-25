#include "ListBoss.h"

#include "Game.h"

extern Game * game;


ListBoss::ListBoss(){
    //add function to tab
    //add big demon
    tabConstructorBoss.push_back((EntityCaracter *(ListBoss::*)(Enemy*))&ListBoss::set_bigDemon);

    //add function
    tabConstructorBoss.push_back((EntityCaracter *(ListBoss::*)(Enemy*))&ListBoss::set_spider);
}

EntityCaracter *ListBoss::get_constructeurOnTab(int argIndex, Enemy * argEnemy){
    return (this->*tabConstructorBoss.at(argIndex))(argEnemy);
}

int ListBoss::get_sizeTabConstructeurEnemy(){
    return tabConstructorBoss.size();
}

EntityCaracter *ListBoss::set_bigDemon(Enemy * argEnemy){
    //create a new temporary entity
    EntityCaracter * tmpEntity = new EntityCaracter();

    //set entity as enemy
    tmpEntity->set_PlayerOrEnemy("Boss");

    //set displacement
    tmpEntity->set_displacement(80, game->fps);

    //set health
    tmpEntity->set_maxHealth(300);
    tmpEntity->set_actualHealth(tmpEntity->get_maxHealth());

    //set rate of fire
    argEnemy->set_rateFire(10);

    //set damage
    argEnemy->set_damage(15);

    //set status (test)
    tmpEntity->set_status(0);

    //set index sprite
    tmpEntity->set_indexSprite(0);

    //set value of verifRotationEnemy
    tmpEntity->set_verifRotation(true);

    //set invulnerability to true
    tmpEntity->set_invulnerability(true);

    //set Sprite entity
    //Sprite idle
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_idle_anim_f0.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_idle_anim_f1.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_idle_anim_f2.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_idle_anim_f3.png", 0);
    //Sprite Run
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_run_anim_f0.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_run_anim_f1.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_run_anim_f2.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/big_demon/big_demon_run_anim_f3.png", 1);

    //set Current Sprite
    tmpEntity->set_currentSprite("");

    //set size entity
    tmpEntity->set_sizeEntity(tmpEntity->get_currentSprite().width(), tmpEntity->get_currentSprite().height());

    //set entity coord
    tmpEntity->set_originEntity(tmpEntity->get_widthEntity() / 2, tmpEntity->get_heightEntity() / 2);

    //set collider
    //set size collider
    tmpEntity->set_colliderSize(2, 2);

    //position
    tmpEntity->colliderBottom = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderBottom->setPos(tmpEntity->get_widthEntity()/2 - tmpEntity->get_widthCollider()/2, tmpEntity->get_heightEntity() + tmpEntity->get_heightCollider() * 0.5);
    tmpEntity->colliderTop = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderTop->setPos(tmpEntity->get_widthEntity()/2 - tmpEntity->get_widthCollider()/2, -tmpEntity->get_heightCollider() * 1.5);
    tmpEntity->colliderLeft = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderLeft->setPos(-tmpEntity->get_widthCollider() * 1.5, tmpEntity->get_heightEntity()/2 - tmpEntity->get_heightCollider()/2 );
    tmpEntity->colliderRight = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderRight->setPos(tmpEntity->get_widthEntity()  + tmpEntity->get_widthCollider() * 0.5, tmpEntity->get_heightEntity()/2 - tmpEntity->get_heightCollider()/2);


    //Path image projectil shooted by enemy
    argEnemy->set_pathProjectil(":/Source/Source/Image/projectil/Projectil_1.png");

    //set number of point get by the playe when enemy die
    argEnemy->set_point(100);

    //set speed projectil
    argEnemy->set_speedProjectil(150);

    //define attack
    argEnemy->set_attack(&Enemy::multipleSimpleShoot);

    //define parameter attack
    argEnemy->set_angleConeAttack(40);
    argEnemy->set_nbShootAttack(8);

    return tmpEntity;
}

EntityCaracter *ListBoss::set_spider(Enemy *argEnemy){
    //create a new temporary entity
    EntityCaracter * tmpEntity = new EntityCaracter();

    //set entity as enemy
    tmpEntity->set_PlayerOrEnemy("Boss");

    //set displacement
    tmpEntity->set_displacement(200, game->fps);

    //set health
    tmpEntity->set_maxHealth(300);
    tmpEntity->set_actualHealth(tmpEntity->get_maxHealth());

    //set rate of fire
    argEnemy->set_rateFire(8);

    //set damage
    argEnemy->set_damage(10);

    //set status (test)
    tmpEntity->set_status(0);

    //set index sprite
    tmpEntity->set_indexSprite(0);

    //set value of verifRotationEnemy
    tmpEntity->set_verifRotation(true);

    //set invulnerability to true
    tmpEntity->set_invulnerability(true);

    //set Sprite entity
    //Sprite idle
    tmpEntity->addSprite(":/Source/Source/Image/Boss/Spider/spider_idle_f1.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/Spider/spider_idle_f2.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/Spider/spider_idle_f3.png", 0);
    //Sprite Run
    tmpEntity->addSprite(":/Source/Source/Image/Boss/Spider/spider_run_f1.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/Spider/spider_run_f2.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Boss/Spider/spider_run_f3.png", 1);

    //set Current Sprite
    tmpEntity->set_currentSprite("");

    //set size entity
    tmpEntity->set_sizeEntity(tmpEntity->get_currentSprite().width(), tmpEntity->get_currentSprite().height());

    //set entity coord
    tmpEntity->set_originEntity(tmpEntity->get_widthEntity() / 2, tmpEntity->get_heightEntity() / 2);

    //set collider
    //set size collider
    tmpEntity->set_colliderSize(2, 2);

    //position
    tmpEntity->colliderBottom = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderBottom->setPos(tmpEntity->get_widthEntity()/2 - tmpEntity->get_widthCollider()/2, tmpEntity->get_heightEntity() + tmpEntity->get_heightCollider() * 0.5);
    tmpEntity->colliderTop = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderTop->setPos(tmpEntity->get_widthEntity()/2 - tmpEntity->get_widthCollider()/2, -tmpEntity->get_heightCollider() * 1.5);
    tmpEntity->colliderLeft = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderLeft->setPos(-tmpEntity->get_widthCollider() * 1.5, tmpEntity->get_heightEntity()/2 - tmpEntity->get_heightCollider()/2 );
    tmpEntity->colliderRight = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderRight->setPos(tmpEntity->get_widthEntity()  + tmpEntity->get_widthCollider() * 0.5, tmpEntity->get_heightEntity()/2 - tmpEntity->get_heightCollider()/2);


    //Path image projectil shooted by enemy
    argEnemy->set_pathProjectil(":/Source/Source/Image/projectil/projectil_flame_2.png");

    //set number of point get by the playe when enemy die
    argEnemy->set_point(100);

    //set speed projectil
    argEnemy->set_speedProjectil(150);

    //define attack
    argEnemy->set_attack(&Enemy::multipleSimpleShoot);

    //define parameter attack
    argEnemy->set_angleConeAttack(20);
    argEnemy->set_nbShootAttack(3);

    return tmpEntity;
}
