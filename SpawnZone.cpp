#include "SpawnZone.h"
#include "Game.h"
#include "Enemy.h"

#include <QGraphicsScene>
#include <QDebug>

extern Game * game;

SpawnZone::SpawnZone(double argX, double argY, double argWidth, double argHeight, std::string typeOfRoom){
    //set a rect to define the spawn zone
    setRect(argX, argY, argHeight, argWidth);

    //setPen(Qt::NoPen);

    //set the type of the room
    type = typeOfRoom;
}

void SpawnZone::spawn()
{
    if(type.compare("monsterRoom") == 0){
        spawnMonsterRoom();
    }
    else if(type.compare("gift")){

    }
}

void SpawnZone::playerEnterSpawnZone()
{
    //change the status of all enemy in room
    if(type.compare("monsterRoom") == 0){
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

void SpawnZone::spawnMonsterRoom()
{
    //set the number of monster in the room (10 is for test, in futur set with level or caracter in donjon)
    monsterNumber = rand()%(10 - 5) + 5;
    qDebug() << QString::fromStdString(type) << monsterNumber;

    //Create every enemy
    for(int indexNMonster = 0; indexNMonster < monsterNumber; indexNMonster++){
        //create a new enemy
        Enemy * enemy = new Enemy();

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


