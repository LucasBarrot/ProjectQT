#include "SpawnZone.h"
#include "Game.h"
#include "Enemy.h"
#include "Room.h"

#include <QGraphicsScene>
#include <QDebug>
#include <random>

extern Game * game;

SpawnZone::SpawnZone(double argX, double argY, double argWidth, double argHeight, std::string typeOfRoom){
    //set a rect to define the spawn zone
    setRect(argX, argY, argHeight, argWidth);

    //setPen(Qt::NoPen);

    //set the type of the room
    type = typeOfRoom;
}

void SpawnZone::spawn(int argSize)
{
    if(type.compare("monsterRoom") == 0){
        spawnMonsterRoom(argSize);
    }
    else if(type.compare("giftRoom") == 0){
        chest = new Chest();
        chest->setParentItem(this);
        chest->setPos(rect().width() / 2 - chest->boundingRect().width()/2 , rect().height()/2 - chest->boundingRect().height()/2);
    }
    else if(type.compare("bossRoom") == 0){
        qDebug() << "Boss Room";
        Enemy * enemy = new Enemy(rand() % argSize, true);

        //add to tabEnemy
        tabEnemy.append(enemy);

        //scene()->addItem(enemy);

        enemy->set_objectOfEnemyInScene();

        enemy->setParentItem(this);
    }
}

void SpawnZone::playerEnterSpawnZone(){
    //change the status of all enemy in room
    if(type.compare("monsterRoom") == 0 || type.compare("bossRoom") == 0){
        for(int indexEnemy = 0; indexEnemy < tabEnemy.size(); ++indexEnemy){
            tabEnemy.at(indexEnemy)->set_ToAttackMode();
        }        
    }
}

void SpawnZone::set_enemyInScene(){
    for(int indexEnemy = 0; indexEnemy < tabEnemy.size(); ++indexEnemy){
        scene()->addItem(tabEnemy.at(indexEnemy));

        tabEnemy.at(indexEnemy)->set_objectOfEnemyInScene();
    }
}

void SpawnZone::spawnDoorToNextLevel(){
    DoorToNextLevel * door = new DoorToNextLevel();

    door->setParentItem(this);

    door->setPos(rect().width() /2 - door->boundingRect().width() /2, rect().height()/2 - door->boundingRect().height() / 2);
}

void SpawnZone::destructionSpawnZone(){
    for(int indexMonster = tabEnemy.size() - 1; 0 <= indexMonster; --indexMonster){
        qDebug() << tabEnemy.size();
        tabEnemy.takeAt(indexMonster)->destructionEnemy();

//        qDebug() << tabEnemy.size();
//        tabEnemy.remove(indexMonster);
    }


    delete this;
}

void SpawnZone::spawnMonsterRoom(int argSize)
{
    //set the number of monster in the room (10 is for test, in futur set with level or caracter in donjon)
    monsterNumber = rand()%(10 - 5) + 5;
    qDebug() << QString::fromStdString(type) << monsterNumber;

    //Create every enemy
    for(int indexNMonster = 0; indexNMonster < monsterNumber; indexNMonster++){
        //create a new enemy
        Enemy * enemy = new Enemy(rand() % argSize, false);

        //add to tabEnemy
        tabEnemy.append(enemy);

        scene()->addItem(enemy);

        //setPos in scene
        enemy->setPos(rand()%((int(rect().width()) - 10) - 10) + 10,  rand()%((int(rect().width()) - 10) - 10) + 10);
        enemy->set_prevPos(QPointF(rand()%((int(rect().width()) - 10) - 10) + 10,  rand()%((int(rect().width()) - 10) - 10) + 10));

        enemy->set_objectOfEnemyInScene();

        enemy->setParentItem(this);
    }
}


