#include "RecapGame.h"

#include "Game.h"

extern Game * game;

RecapGame::RecapGame(){
    double widthScreen = game->width();
    double heightScreen = game->height();

    QGraphicsTextItem * GameOverText = new QGraphicsTextItem();

    GameOverText->setPlainText(QString("Game Over"));
    GameOverText->setDefaultTextColor(Qt::red);
    GameOverText->setFont(QFont("times",16));

    GameOverText->setPos(widthScreen / 2 - GameOverText->boundingRect().width()/ 2,
                         heightScreen / 2 - GameOverText->boundingRect().height() / 2 - 50);

    addItem(GameOverText);



    //score and level
    //add number of level covered text
    QGraphicsTextItem * countLevelText = new QGraphicsTextItem();

    countLevelText->setPlainText(QString("Nb° of level covered : ") +  QString::number(game->get_nbLevelWorld()));
    countLevelText->setDefaultTextColor(Qt::red);
    countLevelText->setFont(QFont("times",16));

    //add score text
    QGraphicsTextItem * scoreText = new QGraphicsTextItem();

    scoreText->setPlainText(QString("score : ") +  QString::number(game->get_score()));
    scoreText->setDefaultTextColor(Qt::red);
    scoreText->setFont(QFont("times",16));

    //calculate the total width of the two text
    double widthCountScoreText = countLevelText->boundingRect().width() + scoreText->boundingRect().width() + 10;

    //position the 2 text
    countLevelText->setPos(game->width() / 2 - widthCountScoreText / 2,
                           GameOverText->pos().y() + GameOverText->boundingRect().height() + 20);

    scoreText->setPos(countLevelText->pos().x() + countLevelText->boundingRect().width() + 10,
                      GameOverText->pos().y() + GameOverText->boundingRect().height() + 20);

    addItem(countLevelText);
    addItem(scoreText);


    // button resume
    buttonGoMenu= new QPushButton("Resume game");

    buttonGoMenu->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    connect(buttonGoMenu, SIGNAL (pressed()), this, SLOT(handleButtonGoMenu()));

    buttonGoMenu->setContextMenuPolicy(Qt::CustomContextMenu);

    proxyGoMenu = new QGraphicsProxyWidget();

    proxyGoMenu->setWidget(buttonGoMenu);

    proxyGoMenu->setPos(widthScreen / 2 - proxyGoMenu->boundingRect().width() / 2,
                        countLevelText->pos().y() + countLevelText->boundingRect().height() + 20);

    addItem(proxyGoMenu);
}

void RecapGame::destructionRecap(){
    proxyGoMenu->setWidget(NULL);

    buttonGoMenu->deleteLater();

    proxyGoMenu->setParentItem(NULL);

    delete  proxyGoMenu;

    delete this;
}

void RecapGame::handleButtonGoMenu(){
    destructionRecap();

    game->closeRecapToMenu();
}
