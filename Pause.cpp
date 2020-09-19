#include "Pause.h"

#include "Game.h"

#include <chrono>
#include <thread>


extern Game* game;

Pause::Pause(){
    buttonResume = new QPushButton("Resume game");

    buttonResume->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    connect(buttonResume, SIGNAL (pressed()), this, SLOT (handleButtonResume()));

    buttonResume->setContextMenuPolicy(Qt::CustomContextMenu);

    proxy = new QGraphicsProxyWidget();

    proxy->setWidget(buttonResume);

    addItem(proxy);


}

void Pause::destructionPause()
{


    proxy->setWidget(NULL);

    buttonResume->deleteLater();

    proxy->setParentItem(NULL);

    delete proxy;

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    delete this;
}

void Pause::handleButtonResume(){

    game->closeOption();
}
