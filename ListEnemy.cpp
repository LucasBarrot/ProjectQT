#include "ListEnemy.h"

ListEnemy::ListEnemy(){
    tabConstructorEnemy.push_back((EntityCaracter *(ListEnemy::*)(Enemy*))&ListEnemy::set_necromancer);
}

EntityCaracter *ListEnemy::get_constructeurOnTab(int argIndex, Enemy * argEnemy){
    return (this->*tabConstructorEnemy.at(argIndex))(argEnemy);
}

int ListEnemy::get_sizeTabConstructeurEnemy(){
    return tabConstructorEnemy.size();
}



EntityCaracter *ListEnemy::set_necromancer(Enemy * argEnemy){


    //create a new temporary entity
    EntityCaracter * tmpEntity = new EntityCaracter();

    //set entity as enemy
    tmpEntity->set_PlayerOrEnemy("Enemy");

    //set the parent of the entity to this class(player)
    //entity->setParentItem(this);

    //set displacement
    tmpEntity->set_displacement(0, 0);

    //set health
    tmpEntity->set_maxHealth(25);
    tmpEntity->set_actualHealth(tmpEntity->get_maxHealth());

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
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f0.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f1.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f2.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_idle_anim_f3.png", 0);
    //Sprite Run
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f0.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f1.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f2.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Necromancer/necromancer_run_anim_f3.png", 1);

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

    return tmpEntity;
}
