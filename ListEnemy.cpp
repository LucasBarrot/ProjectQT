#include "ListEnemy.h"

#include "Game.h"

extern Game * game;

ListEnemy::ListEnemy(){
    //add configurator to the list of function
    //add necromancer
    tabConstructorEnemy.push_back((EntityCaracter *(ListEnemy::*)(Enemy*))&ListEnemy::set_necromancer);
    //add octorok
    tabConstructorEnemy.push_back((EntityCaracter *(ListEnemy::*)(Enemy*))&ListEnemy::set_octorok);
    //add BuzzBlob & CukeMan
    tabConstructorEnemy.push_back((EntityCaracter *(ListEnemy::*)(Enemy*))&ListEnemy::set_buzzBlob_CukeMan);

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

    //set displacement
    tmpEntity->set_displacement(100, game->fps);

    //set health
    tmpEntity->set_maxHealth(25);
    tmpEntity->set_actualHealth(tmpEntity->get_maxHealth());

    //set rate of fire
    argEnemy->set_rateFire(0.2);

    //set damage enemy
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

    //set number of point get by the playe when enemy die
    argEnemy->set_point(10);

    //set attack enemy
    argEnemy->set_attack(&Enemy::shootSimple);

    return tmpEntity;
}

EntityCaracter *ListEnemy::set_octorok(Enemy *argEnemy){
    //create a new temporary entity
    EntityCaracter * tmpEntity = new EntityCaracter();

    //set entity as enemy
    tmpEntity->set_PlayerOrEnemy("Enemy");

    //set displacement
    tmpEntity->set_displacement(50, game->fps);

    //set health
    tmpEntity->set_maxHealth(15);
    tmpEntity->set_actualHealth(tmpEntity->get_maxHealth());

    //set rate of fire
    argEnemy->set_rateFire(0.5);

    //set se(15);

    //set status
    tmpEntity->set_status(0);

    //set index sprite
    tmpEntity->set_indexSprite(0);

    //set value of verifRotationEnemy
    tmpEntity->set_verifRotation(true);

    //set invulnerability to true
    tmpEntity->set_invulnerability(true);

    //set Sprite entity
    //Sprite idle
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Octorok/Octorok_f0.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Octorok/Ocotorok_f1.png", 0);

    //Sprite Run
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Octorok/Octorok_f0.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Octorok/Ocotorok_f1.png", 1);

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
    argEnemy->set_pathProjectil(":/Source/Source/Image/projectil/Rock_projectil.png");

    //set number of point get by the player when enemy die
    argEnemy->set_point(5);

    //set attack enemy
    argEnemy->set_attack(&Enemy::shootSimple);

    return tmpEntity;
}

EntityCaracter *ListEnemy::set_buzzBlob_CukeMan(Enemy *argEnemy){
    //create a new temporary entity
    EntityCaracter * tmpEntity = new EntityCaracter();

    //set entity as enemy
    tmpEntity->set_PlayerOrEnemy("Enemy");

    //set displacement
    tmpEntity->set_displacement(50, game->fps);

    //set health
    tmpEntity->set_maxHealth(15);
    tmpEntity->set_actualHealth(tmpEntity->get_maxHealth());

    //set rate of fire
    argEnemy->set_rateFire(2);

    //set damage enemy
    argEnemy->set_damage(5);

    //set status
    tmpEntity->set_status(0);

    //set index sprite
    tmpEntity->set_indexSprite(0);

    //set value of verifRotationEnemy
    tmpEntity->set_verifRotation(true);

    //set invulnerability to true
    tmpEntity->set_invulnerability(true);

    //set Sprite entity
    //Sprite idle
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/BuzzBlob_CukeMan/BuzzBlob_CukeMan_idle_f0.png", 0);//f0
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/BuzzBlob_CukeMan/BuzzBlob_CukeMan_idle_f1.png", 0);//f1
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/BuzzBlob_CukeMan/BuzzBlob_CukeMan_idle_f2.png", 0);//f2

    //Sprite Run
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/BuzzBlob_CukeMan/BuzzBlob_CukeMan_Run_f0.png", 1);//f0
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/BuzzBlob_CukeMan/BuzzBlob_CukeMan_Run_f1.png", 1);//f1

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
    argEnemy->set_pathProjectil(":/Source/Source/Image/projectil/Miasme_Projectil.png");

    //set number of point get by the player when enemy die
    argEnemy->set_point(8);

    //set attack enemy
    argEnemy->set_attack(&Enemy::shootSimple);

    return tmpEntity;
}
