#ifndef SPAWNZONE_H
#define SPAWNZONE_H

#include <QGraphicsRectItem>

#include "Enemy.h"
#include "Chest.h"


class SpawnZone : public QGraphicsRectItem{
public:
    SpawnZone(double argX, double argY, double argWidth, double argHeight, std::string typeOfRoom);

    //define wich room is it
    void spawn();

    //set the enemy of the room to attack mode
    void playerEnterSpawnZone();

    //void set_enemy in scene
    void set_enemyInScene();

    //tab of all enemy in this room of this gen
    QVector<Enemy*>  tabEnemy;

    //chest in this room of this gen
    Chest * chest;
private:

    //rect that define the zone where object need to spawn
    QGraphicsRectItem * spawnZone;

    //type of the room
    std::string type;

    //Number of monster in the room
    int monsterNumber;

    //spawn
    //spawn monster
    void spawnMonsterRoom();
};

#endif // SPAWNZONE_H
