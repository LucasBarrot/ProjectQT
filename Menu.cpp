#include "Menu.h"

#include "Game.h"

extern Game * game;

Menu::Menu(double argWidth, double argHeight){
    //set text
    double widthScreen = argWidth;
    double heightScreen = argHeight;

    QGraphicsTextItem * menuText = new QGraphicsTextItem();

    menuText->setPlainText(QString("Rogue Like Zelda"));
    menuText->setDefaultTextColor(Qt::white);
    menuText->setFont(QFont("Times",16));

    menuText->setPos(widthScreen / 2 - menuText->boundingRect().width()/ 2, heightScreen / 2 - menuText->boundingRect().height() / 2 - 50);

    addItem(menuText);

    //button launch a game
    buttonLaunchGame = new QPushButton("Lauch new game");

    buttonLaunchGame->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    connect(buttonLaunchGame, SIGNAL (pressed()), this, SLOT (handleButtonLaunchGame()));

    buttonLaunchGame->setContextMenuPolicy(Qt::CustomContextMenu);

    proxy = new QGraphicsProxyWidget();

    proxy->setWidget(buttonLaunchGame);

    proxy->setZValue(5);

    proxy->setPos(widthScreen / 2 - proxy->boundingRect().width() / 2,
                        menuText->pos().y() + menuText->boundingRect().height() + 20);

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
