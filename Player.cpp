#include "Player.h"

#include "Wall.h"
#include "Game.h"
#include "Enemy.h"

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

    if (!event->isAutoRepeat()){
        if((event->key() == Qt::Key_Q || event->key() == Qt::Key_Z || event->key() == Qt::Key_D || event->key() == Qt::Key_S)){
            keysPressed_.insert(event->key());
            qDebug() << event->key() << keysPressed_.size();

            if(keysPressed_.size() != 0 && verifFirstKeyMOuvement == true){

                verifFirstKeyMOuvement = false;
                playerEntity->set_status(1);
                playerEntity->changeSprite();
            }
        }
        else if (event->key() == Qt::Key_Space){
            action();
        }

    }


}

void Player::keyReleaseEvent(QKeyEvent *event){



    if (!event->isAutoRepeat()){
        if((event->key() == Qt::Key_Q || event->key() == Qt::Key_Z || event->key() == Qt::Key_D || event->key() == Qt::Key_S)){
            keysPressed_.erase(event->key());

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

    bool verifChest = false;
    int indexColliderStop;

    //check every colliding items if it is a chest
    for (int indexCollider = 0, n = colliding_items.size(); indexCollider < n; ++indexCollider){
         if(typeid (*(colliding_items[indexCollider])).name() == typeid(Chest).name()){
             verifChest = true;
             indexColliderStop = indexCollider;
             break;
         }
    }

    //if player collide with a chest and space is pressed, open the chest
    if(verifChest){
        Chest * chestTouchByPlayer = dynamic_cast<Chest*>(colliding_items.at(indexColliderStop));
        chestTouchByPlayer->openChest();
    }
}

//add weapon to player from inventory
void Player::addWeapon(EntityWeapon * argEntity){
    //add weapon
     weapon = new Weapon(argEntity);

     weapon->setParentItem(this);
}

//define entity player
Entity * Player::set_entityPlayer(int fps)
{
    Entity * entity = new Entity();

    //set entity is player
    entity->set_PlayerOrEnemy(true);

    //set the parent of the entity to this class(player)
    entity->setParentItem(this);

    //set displacement
    entity->set_displacement(150, fps);

    //set status (test)
    entity->set_status(0);

    //set healtyh
    entity->set_maxHealth(100);
    entity->set_actualHealth(entity->get_actualHealth());

    //set index sprite
    entity->set_indexSprite(0);

    //set verif rotation player
    entity->set_verifRotation(true);

    //set Sprite entity
    //Sprite idle
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f0.png", 0);
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f1.png", 0);
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f2.png", 0);
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f3.png", 0);
    //Sprite Run
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f0.png", 1);
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f1.png", 1);
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f2.png", 1);
    entity->addSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_run_anim_f3.png", 1);

    //set Current Sprite
    entity->set_currentSprite(":/Source/Source/Image/Caractere/Wizzard/wizzard_m_idle_anim_f0.png");

    //set size entity
    entity->set_sizeEntity(entity->get_currentSprite().width(), entity->get_currentSprite().height());

    //set entity coord
    entity->set_originEntity(entity->get_widthEntity() / 2, entity->get_heightEntity() / 2);

    //set collider
    //set size collider
    entity->set_colliderSize(2, 2);
    //position
    entity->colliderBottom = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderBottom->setPos(pos().x() + entity->get_widthEntity()/2 - entity->get_widthCollider()/2, pos().y() +  entity->get_heightEntity() - entity->get_heightCollider());
    entity->colliderTop = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderTop->setPos(pos().x() + entity->get_widthEntity()/2 - entity->get_widthCollider()/2, pos().y());
    entity->colliderLeft = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderLeft->setPos(pos().x() + entity->get_widthCollider(),  pos().y() + entity->get_heightEntity()/2 - entity->get_heightCollider()/2 );
    entity->colliderRight = new Collider(entity->get_widthCollider(), entity->get_heightCollider());
    entity->colliderRight->setPos(pos().x() +  entity->get_widthEntity()  - entity->get_widthCollider(), pos().y() + entity->get_heightEntity()/2 - entity->get_heightCollider()/2);

    entity->setTransformOriginPoint(0,0);

    return entity;
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





