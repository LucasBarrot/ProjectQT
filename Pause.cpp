#include "Pause.h"

#include "Game.h"

#include <chrono>
#include <thread>
#include <QGraphicsTextItem>
#include <QFont>

#include <QDebug>


extern Game* game;

Pause::Pause(){
    double widthScreen = game->width();
    double heightScreen = game->height();

    QGraphicsTextItem * pauseText = new QGraphicsTextItem();

    pauseText->setPlainText(QString("Pause"));
    pauseText->setDefaultTextColor(Qt::red);
    pauseText->setFont(QFont("times",16));

    pauseText->setPos(widthScreen / 2 - pauseText->boundingRect().width()/ 2, heightScreen / 2 - pauseText->boundingRect().height() / 2 - 50);

    addItem(pauseText);

    QGraphicsTextItem * countLevelText = new QGraphicsTextItem();

    countLevelText->setPlainText(QString("Nb° of level covered : ") +  QString::number(game->get_nbLevelWorld()));
    countLevelText->setDefaultTextColor(Qt::red);
    countLevelText->setFont(QFont("times",16));

    QGraphicsTextItem * scoreText = new QGraphicsTextItem();

    scoreText->setPlainText(QString("score : ") +  QString::number(game->get_score()));
    scoreText->setDefaultTextColor(Qt::red);
    scoreText->setFont(QFont("times",16));

    double widthCountScoreText = countLevelText->boundingRect().width() + scoreText->boundingRect().width() + 10;

    countLevelText->setPos(game->width() / 2 - widthCountScoreText / 2,
                           pauseText->pos().y() + pauseText->boundingRect().height() + 20);

    scoreText->setPos(countLevelText->pos().x() + countLevelText->boundingRect().width() + 10,
                      pauseText->pos().y() + pauseText->boundingRect().height() + 20);

    addItem(countLevelText);
    addItem(scoreText);


    // button resume
    buttonResume = new QPushButton("Resume game");

    buttonResume->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    connect(buttonResume, SIGNAL (pressed()), this, SLOT (handleButtonResume()));

    buttonResume->setContextMenuPolicy(Qt::CustomContextMenu);

    proxyResume = new QGraphicsProxyWidget();

    proxyResume->setWidget(buttonResume);

    proxyResume->setPos(widthScreen / 2 - proxyResume->boundingRect().width() / 2,
                        countLevelText->pos().y() + countLevelText->boundingRect().height() + 20);

    addItem(proxyResume);

    //button quit
    buttonQuitToMenu = new QPushButton("Quit game to menu");

    buttonQuitToMenu->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    connect(buttonQuitToMenu, SIGNAL (pressed()), this, SLOT (handleButtonQuitToMenu()));

    buttonQuitToMenu->setContextMenuPolicy(Qt::CustomContextMenu);

    proxyQuitToMenu = new QGraphicsProxyWidget();

    proxyQuitToMenu->setWidget(buttonQuitToMenu);

    proxyQuitToMenu->setPos(widthScreen / 2 - proxyQuitToMenu->boundingRect().width() / 2, proxyResume->pos().y() + pauseText->boundingRect().height() + 20);

    addItem(proxyQuitToMenu);

}

void Pause::destructionPause(){
    proxyResume->setWidget(NULL);

    buttonResume->deleteLater();

    proxyResume->setParentItem(NULL);

    delete proxyResume;

    proxyQuitToMenu->setWidget(NULL);

    buttonQuitToMenu->deleteLater();

    proxyQuitToMenu->setParentItem(NULL);

    delete proxyQuitToMenu;

    delete this;
}

void Pause::handleButtonResume(){
    game->closeOption();
}

void Pause::handleButtonQuitToMenu(){
    destructionPause();

    game->closeGameToRecap();

    //buttonQuitToMenu->releaseMouse();
}
