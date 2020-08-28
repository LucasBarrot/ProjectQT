#include "Update.h"

#include <QGraphicsScene>
#include <QTimer>

extern Game * game;

Update::Update(double argFps)
{
    fps = argFps;
    //set connect with a timer base on fps
    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Update::updateBaseOnFps);
    timer->start( 1000/fps);
    indexFps = 0;
}

void Update::updateBaseOnFps()
{
    if(indexFps % 1 == 0){
        game->player->moving();
    }

    for(int indexProjectil = 0; indexProjectil < game->tabProjectil.size(); indexProjectil++){
        game->tabProjectil.at(indexProjectil)->moveProjectil();
    }

    if(indexFps%20 == 0){
        game->player->updateSprite();
    }



    indexFps++;

    if(indexFps > fps){
        indexFps = 0;
    }



}
