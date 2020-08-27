#include "Update.h"

extern Game * game;

Update::Update(double argFps)
{
    fps = argFps;
    //set connect with a timer base on fps
    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&Update::updateBaseOnFps);
    timer->start(1000/fps);
}

void Update::updateBaseOnFps()
{
    game->player->moving();

    for(int indexProjectil = 0; indexProjectil < game->tabProjectil.size(); indexProjectil++){
        game->tabProjectil.at(indexProjectil)->moveProjectil();
    }
}
