#ifndef IMAGINAWARS_H
#define IMAGINAWARS_H

#include "engine/game.h"
#include "game/gamemap.h"
#include "game/walkpathfindingcomponent.h"
#include "game/effectspritecomponent.h"
#include "game/soldier.h"

#include <sstream>
#include <iomanip>


class ImaginaWars : public Game
{
public:

    ImaginaWars(int _fps = 60);

    void startGame() override;

protected:

    void initShaders() override;
    void initTextures() override;

    void mouseReleaseEvent(QMouseEvent *e) override;


    GameMap *gm;
    Soldier *spr;
};

#endif // IMAGINAWARS_H
