#ifndef IMAGINAWARS_H
#define IMAGINAWARS_H

#include "engine/game.h"
#include "game/gamemap.h"
#include "game/walkpathfindingcomponent.h"

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
    Sprite *spr;
    WalkPathfindingComponent *pathfinding;
};

#endif // IMAGINAWARS_H
