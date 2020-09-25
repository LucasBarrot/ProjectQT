#include <QApplication>
#include "Game.h"

#include "Menu.h"

Game * game;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    game->show();

    return a.exec();
}
