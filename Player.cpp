#include "Player.h"

#include "Wall.h"
#include "Game.h"
#include "Enemy.h"
#include "WeaponOnGround.h"

#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <math.h>

extern Game * game;

Player::Player(double fps){
    //set verif key
    verifFirstKeyMOuvement = true;

    //set player
    playerEntity = set_entityPlayer(fps);
}

void Player::keyPressEvent(QKeyEvent *event){
    //do not repeat key press
    if (!event->isAutoRepeat()){
        //only Z Q S D can enter
        if((event->key() == Qt::Key_Q || event->key() == Qt::Key_Z || event->key() == Qt::Key_D || event->key() == Qt::Key_S)){
            keysPressed_.insert(event->key());
            //if the player press one touch or more change the animation of idle to mouvement
            if(keysPressed_.size() != 0 && verifFirstKeyMOuvement == true){

                verifFirstKeyMOuvement = false;
                playerEntity->set_status(1);
                playerEntity->changeSprite();
            }
        }
        //only space can enter
        else if (event->key() == Qt::Key_Space){
            action();
        }
        else if(event->key() == Qt::Key_Ampersand && weapon->entityWeapon != game->inventory->get_weapon_1() && game->inventory->get_initializedWeapon_1()){
            changeWeapon(1);
        }
        else if(event->key() == Qt::Key_Eacute && weapon->entityWeapon != game->inventory->get_weapon_2() && game->inventory->get_initializedWeapon_2()){
            changeWeapon(2);
        }

    }


}

void Player::keyReleaseEvent(QKeyEvent *event){

    //when a key is release do this and is not repeate do this
    if (!event->isAutoRepeat()){
        //if the key release is Z, Q, S, D because we don't want other touch like space to enter the if
        if((event->key() == Qt::Key_Q || event->key() == Qt::Key_Z || event->key() == Qt::Key_D || event->key() == Qt::Key_S)){
            keysPressed_.erase(event->key());
            //if no ther touch press chenge the animation of movement to idle
            if(keysPressed_.size() == 0 && (event->key() == Qt::Key_Q || event->key() == Qt::Key_Z || event->key() == Qt::Key_D || event->key() == Qt::Key_S)){
                playerEntity->set_status(0);
                verifFirstKeyMOuvement = true;
                playerEntity->changeSprite();
            }
        }
    }
}

QPointF Player::getOriginMapToScene(){
    return mapToScene(this->pos() + playerEntity->get_pointCoordOrgin());
}

void Player::set_angle(double argAngle)
{
    angle = argAngle;
}

void Player::healthPlayerChange(double argHealth){
    //change health in entity
    playerEntity->set_actualHealth(argHealth);

    if(playerEntity->get_actualHealth() > playerEntity->get_maxHealth()){
        playerEntity->set_maxHealth(playerEntity->get_actualHealth());
    }

    //change health in UI

}

double Player::get_angle()
{
    return angle;
}

void Player::set_objectOfPlayerInScene(){
    setRect(0,0, playerEntity->get_widthEntity(), playerEntity->get_heightEntity());
    //setPen(Qt::NoPen);
    scene()->addItem(playerEntity);
    scene()->addItem(playerEntity->colliderBottom);
    scene()->addItem(playerEntity->colliderTop);
    scene()->addItem(playerEntity->colliderLeft);
    scene()->addItem(playerEntity->colliderRight);
}

void Player::action(){
    //define list of QGraphics Item that contain every colliding items
    QList<QGraphicsItem *> colliding_items = this->collidingItems();

    //check every colliding items if it is a chest
    for (int indexCollider = 0, n = colliding_items.size(); indexCollider < n; ++indexCollider){
        //if chest detect
         if(typeid (*(colliding_items[indexCollider])).name() == typeid(Chest).name()){
             Chest * chestTouchByPlayer = dynamic_cast<Chest*>(colliding_items.at(indexCollider));
             if(!chestTouchByPlayer->get_chestOpen()){
                 chestTouchByPlayer->openChest();
                 break;
             }
         }
        //if weapon on ground detect
         if(typeid (*(colliding_items[indexCollider])).name() == typeid(WeaponOnGround).name()){
             WeaponOnGround * weaponOnGroundTouchByPlayer = dynamic_cast<WeaponOnGround*>(colliding_items.at(indexCollider));
             game->inventory->changeWeapon(weaponOnGroundTouchByPlayer->get_entityWeaponOnGround());
             delete weaponOnGroundTouchByPlayer;
             break;
         }
         if(typeid (*(colliding_items[indexCollider])).name() == typeid(DoorToNextLevel).name()){
             game->newLevel();
             break;
         }
    }
}

//add weapon to player from inventory
void Player::addWeapon(EntityWeapon * argEntity){
    //add weapon
     weapon = new Weapon(argEntity);

     weapon->setParentItem(this);
}

void Player::changeWeapon(int indexWeapon){
    if(indexWeapon == 1){
        weapon->entityWeapon = game->inventory->get_weapon_1();
        weapon->weaponEquipeChange();
    }
    else if(indexWeapon == 2){
        weapon->entityWeapon = game->inventory->get_weapon_2();
        weapon->weaponEquipeChange();
    }
}


//define entity player
EntityCaracter * Player::set_entityPlayer(int fps)
{
    EntityCaracter * tmpEntity = new EntityCaracter();

    //set entity is player
    tmpEntity->set_PlayerOrEnemy("Player");

    //set the parent of the entity to this class(player)
    tmpEntity->setParentItem(this);

    //set displacement
    tmpEntity->set_displacement(150, fps);

    //set status (test)
    tmpEntity->set_status(0);

    //set healtyh
    tmpEntity->set_maxHealth(100);
    tmpEntity->set_actualHealth(tmpEntity->get_actualHealth());

    //set index sprite
    tmpEntity->set_indexSprite(0);

    //set verif rotation player
    tmpEntity->set_verifRotation(true);

    //set Sprite entity
    //Sprite idle
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f0.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f1.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f2.png", 0);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f3.png", 0);
    //Sprite Run
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f0.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f1.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f2.png", 1);
    tmpEntity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f3.png", 1);

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
    tmpEntity->colliderBottom->setPos(pos().x() + tmpEntity->get_widthEntity()/2 - tmpEntity->get_widthCollider()/2, pos().y() +  tmpEntity->get_heightEntity() - tmpEntity->get_heightCollider());
    tmpEntity->colliderTop = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderTop->setPos(pos().x() + tmpEntity->get_widthEntity()/2 - tmpEntity->get_widthCollider()/2, pos().y());
    tmpEntity->colliderLeft = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderLeft->setPos(pos().x() + tmpEntity->get_widthCollider(),  pos().y() + tmpEntity->get_heightEntity()/2 - tmpEntity->get_heightCollider()/2 );
    tmpEntity->colliderRight = new Collider(tmpEntity->get_widthCollider(), tmpEntity->get_heightCollider());
    tmpEntity->colliderRight->setPos(pos().x() +  tmpEntity->get_widthEntity()  - tmpEntity->get_widthCollider(), pos().y() + tmpEntity->get_heightEntity()/2 - tmpEntity->get_heightCollider()/2);

    tmpEntity->setTransformOriginPoint(0,0);

    return tmpEntity;
}

//fonction to move the player
void Player::moving()
{   
    //
    int xDisplacement = 0, yDisplacement = 0, xSign = 0, ySign = 0;
    bool verifLeft = false, verifRight = false, verifTop = false, verifBottom = false;

    bool zPressed = keysPressed_.count(Qt::Key_Z);
    bool sPressed = keysPressed_.count(Qt::Key_S);
    bool qPressed = keysPressed_.count(Qt::Key_Q);
    bool dPressed = keysPressed_.count(Qt::Key_D);

    if( zPressed || sPressed || qPressed || dPressed){
        if(!(qPressed && dPressed) && (qPressed || dPressed)){
            if (qPressed){
                xDisplacement += -playerEntity->get_displacement();
                yDisplacement += 0;
            }
            if (dPressed){
                xDisplacement += +playerEntity->get_displacement();
                yDisplacement += 0;
            }

            playerEntity->colliderLeft->setPos(pos().x() + xDisplacement + playerEntity->get_widthCollider(),
                                               pos().y() + playerEntity->get_heightEntity()/2 - playerEntity->get_heightCollider()/2 );
            playerEntity->colliderRight->setPos(pos().x() + xDisplacement +  playerEntity->get_widthEntity()  - playerEntity->get_widthCollider(),
                                                pos().y() + playerEntity->get_heightEntity()/2 - playerEntity->get_heightCollider()/2);

            QList<QGraphicsItem *> colliding_items_Left = playerEntity->colliderLeft->collidingItems();
            QList<QGraphicsItem *> colliding_items_Right = playerEntity->colliderRight->collidingItems();

            verifLeft = playerEntity->colliderVerif(colliding_items_Left, typeid(Wall).name(), typeid (Enemy).name(), typeid (Chest).name());
            verifRight = playerEntity->colliderVerif(colliding_items_Right, typeid(Wall).name(), typeid (Enemy).name(), typeid (Chest).name());
        }
        if(!(zPressed && sPressed) && (zPressed || sPressed)){
            if (zPressed){
                xDisplacement += 0;
                yDisplacement += -playerEntity->get_displacement();
            }
            if (sPressed){
                xDisplacement += 0;
                yDisplacement += +playerEntity->get_displacement();
            }

            playerEntity->colliderBottom->setPos(pos().x() + playerEntity->get_widthEntity()/2 - playerEntity->get_widthCollider()/2,
                                                 pos().y() +  playerEntity->get_heightEntity() - playerEntity->get_heightCollider() + 1 + yDisplacement);
            playerEntity->colliderTop->setPos(pos().x() + playerEntity->get_widthEntity()/2 - playerEntity->get_widthCollider()/2,
                                              pos().y() + yDisplacement);

            QList<QGraphicsItem *> colliding_items_Bottom = playerEntity->colliderBottom->collidingItems();
            QList<QGraphicsItem *> colliding_items_Top = playerEntity->colliderTop->collidingItems();

            verifBottom = playerEntity->colliderVerif(colliding_items_Bottom, typeid (Wall).name(), typeid (Enemy).name(), typeid (Chest).name());
            verifTop = playerEntity->colliderVerif(colliding_items_Top, typeid(Wall).name(), typeid (Enemy).name(), typeid (Chest).name());
        }

        if(keysPressed_.size() == 1){
            if(verifBottom == false && sPressed){
                setPos(x(),y()+playerEntity->get_displacement());
            }
            else if (verifTop == false && zPressed){
                setPos(x(),y()-playerEntity->get_displacement());
            }
            else if (verifLeft == false && qPressed){
                setPos(x()-playerEntity->get_displacement(),y());
            }
            else if(verifRight == false && dPressed){
                setPos(x()+playerEntity->get_displacement(),y());
            }
        }
        else {

            if(verifBottom == false && sPressed && verifRight == false && dPressed){
                setPos(x() + int(playerEntity->get_displacement() / sqrt(2)), y() + int(playerEntity->get_displacement() / sqrt(2)));
            }
            else if (verifTop == false && zPressed && verifLeft == false && qPressed ){
                setPos(x() - int(playerEntity->get_displacement() / sqrt(2)),y() - int(playerEntity->get_displacement() / sqrt(2)));
            }
            else if (verifRight == false && dPressed && verifTop == false && zPressed){
                setPos(x() + int(playerEntity->get_displacement() / sqrt(2)),y() - int(playerEntity->get_displacement() / sqrt(2)));
            }
            else if(verifLeft == false && qPressed && verifBottom == false && sPressed){
                setPos(x() - int(playerEntity->get_displacement() / sqrt(2)),y() + int(playerEntity->get_displacement() / sqrt(2)));
            }
        }

        if(verifBottom || verifTop || verifLeft || verifRight) {
            if(sPressed){
                xSign = 0;
                ySign = 1;
                moveCloseToWall(xSign, ySign, playerEntity->colliderBottom);
            }
            if(zPressed){
                xSign = 0;
                ySign = -1;
                moveCloseToWall(xSign, ySign, playerEntity->colliderTop);
            }
            if(qPressed){
                xSign = -1;
                ySign = 0;
                moveCloseToWall(xSign, ySign, playerEntity->colliderLeft);
            }
            if(dPressed){
                xSign = 1;
                ySign = 0;
                moveCloseToWall(xSign, ySign, playerEntity->colliderRight);
            }
        }

        verifPlayerInRoom();

    }

}

void Player::verifPlayerInRoom()
{
    bool verifSpawnZone = false;
    int indexColliderStop = 0;

    QList<QGraphicsItem *> collidingItemsPlayer = this ->collidingItems();

    for (int indexCollider = 0, n = collidingItemsPlayer.size(); indexCollider < n; ++indexCollider){
         if (typeid(*(collidingItemsPlayer[indexCollider])) == typeid (SpawnZone)){
            verifSpawnZone = true;
            indexColliderStop = indexCollider;
            break;
         }
    }


    if(verifSpawnZone && playerIsInRoom != dynamic_cast<SpawnZone*>(collidingItemsPlayer.at(indexColliderStop))){
        //dynamic_cast : we can use the function of SpawnZone class
        playerIsInRoom = dynamic_cast<SpawnZone*>(collidingItemsPlayer.at(indexColliderStop));

        playerIsInRoom->playerEnterSpawnZone();
    }

}

void Player::moveCloseToWall(int xSign, int ySign, Collider * collider)
{
    int xDisplacement = 0, yDisplacement = 0;
    for(int indexSpeed = 0; indexSpeed < playerEntity->get_displacement(); indexSpeed++){
        if(collider == playerEntity->colliderTop or collider == playerEntity->colliderBottom){
            playerEntity->colliderBottom->setPos(pos().x() + playerEntity->get_widthEntity()/2 - playerEntity->get_widthCollider()/2, pos().y() +  playerEntity->get_heightEntity() - playerEntity->get_heightCollider() + yDisplacement);
            playerEntity->colliderTop->setPos(pos().x() + playerEntity->get_widthEntity()/2 - playerEntity->get_widthCollider()/2, pos().y() + yDisplacement);
        }
        else {
            playerEntity->colliderLeft->setPos(pos().x() + xDisplacement  ,  pos().y() + playerEntity->get_heightEntity()/2 - playerEntity->get_heightCollider()/2 );
            playerEntity->colliderRight->setPos(pos().x() + xDisplacement +  playerEntity->get_widthEntity()  - playerEntity->get_widthCollider(), pos().y() + playerEntity->get_heightEntity()/2 - playerEntity->get_heightCollider()/2);
        }

        QList<QGraphicsItem *> colliding_items= collider->collidingItems();

        bool verif =  playerEntity->colliderVerif(colliding_items, typeid (Wall).name(), typeid (Enemy).name(), typeid (Chest).name());

        if(verif){
            break;
        }

        xDisplacement += xSign;
        yDisplacement += ySign;
    }

    setPos(x() + xDisplacement, y() + yDisplacement);
}





