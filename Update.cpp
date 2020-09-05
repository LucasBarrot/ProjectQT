#include "Update.h"

#include <QGraphicsScene>
#include <QTimer>

extern Game * game;

Update::Update(double argFps)
{
    //set fps
    fps = argFps;

    //set connect with a timer base on fps
    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Update::updateBaseOnFps);
    timer->start( 1000/fps);
    indexFps = 0;
}

void Update::updateBaseOnFps()
{
    //move player
    game->player->moving();

    //move projectil
    for(int indexProjectil = 0; indexProjectil < game->tabProjectil.size(); indexProjectil++){
        game->tabProjectil.at(indexProjectil)->updatePositionOnScreen(indexProjectil);
    }

    //change sprite player and enemy
    if(indexFps % int(fps / 3) == 0 && indexFps != 0){
        for(int indexRoom = 0; indexRoom < game->world->tabRoom.size(); indexRoom++){
            Room * tmpRoom = game->world->tabRoom.at(indexRoom);
            for(int indexEnemy = 0; indexEnemy < tmpRoom->spawnZone->tabEnemy.size(); indexEnemy++){
                Enemy * tmpEnemy = tmpRoom->spawnZone->tabEnemy.at(indexEnemy);
                tmpEnemy->UpdateEnemy();
            }
        }

        game->player->playerEntity->chooseSprite();
    }

    //center view on player
    game->centerOn(game->player->x() + game->player->rect().width()/2, game->player->y() + game->player->rect().height()/2);

    //increase index fps
    indexFps++;

    //restart index fps if it is more than the number of fps
    if(indexFps > fps){
        indexFps = 0;
    }



}
