#include "UI.h"

#include "Game.h"

extern Game* game;

UI::UI(){


}

void UI::printOnScreen()
{
    setRect(100 * 0.8, 0, 100*0.2, 200);
    setBrush(Qt::black);
}
