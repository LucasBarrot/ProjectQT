#include "Menu.h"

#include "Game.h"

extern Game * game;

Menu::Menu(){
    buttonLaunchGame = new QPushButton("Lauch new game");

    buttonLaunchGame->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    connect(buttonLaunchGame, SIGNAL (pressed()), this, SLOT (handleButtonLaunchGame()));

    buttonLaunchGame->setContextMenuPolicy(Qt::CustomContextMenu);

    proxy = new QGraphicsProxyWidget();

    proxy->setWidget(buttonLaunchGame);

    proxy->setZValue(5);

    addItem(proxy);
}

void Menu::destructionMenu()
{
    proxy->setWidget(NULL);

    buttonLaunchGame->deleteLater();

    removeItem(proxy);

    delete proxy;

    delete this;

    //clear();
}

void Menu::handleButtonLaunchGame()
{
    game->launchGame();
}
