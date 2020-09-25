#include "Update.h"

#include <QGraphicsScene>
#include <QTimer>

extern Game * game;

Update::Update(double argFps, QTimer * argTimer)
{
    //set fps
    fps = argFps;

    //keep track of the number of fps per second
    indexFps = 0;

    //set first frame
    firstFrame = true;

    //set connect with a timer base on fps
    timer = argTimer;
    connect(timer,&QTimer::timeout,this,&Update::updateBaseOnFps);
    timer->start( 1000/fps);



}

void Update::updateBaseOnFps(){

    if(firstFrame == true){
        firstFrame = false;

        game->ui->printOnScreen();
    }

    //move player
    game->player->moving();

    for(int indexRoom = 0; indexRoom < game->world->tabRoom.size(); indexRoom++){
        Room * tmpRoom = game->world->tabRoom.at(indexRoom);
        for(int indexEnemy = 0; indexEnemy < tmpRoom->spawnZone->tabEnemy.size(); indexEnemy++){
            Enemy * tmpEnemy = tmpRoom->spawnZone->tabEnemy.at(indexEnemy);
            tmpEnemy->UpdateEnemy();
            if(indexFps % int(fps / 3) == 0 && indexFps != 0) {
                tmpEnemy->UpdateSpriteEnemy();
            }
        }
    }

    //change sprite player
    if(indexFps % int(fps / 3) == 0 && indexFps != 0){
        game->player->playerEntity->chooseSprite();
    }

    //move projectil
    for(int indexProjectil = 0; indexProjectil < game->tabProjectil.size(); indexProjectil++){
        game->tabProjectil.at(indexProjectil)->updatePositionOnScreen(indexProjectil);
    }

    //center view on player
    game->centerOn(game->player->x() + game->player->rect().width()/2 + ((game->width()*0.2)/3)/2, game->player->y() + game->player->rect().height()/2);


    //update pos Ui
    game->ui->setPos(game->mapToScene(game->width()*0.8, 0));

    //increase index fps
    indexFps++;

    //restart index fps if it is more than the number of fps
    if(indexFps > fps){
        indexFps = 0;
    }



}
