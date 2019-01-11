#ifndef IMAGINAWARS_H
#define IMAGINAWARS_H

#include "engine/game.h"
#include "game/gamemap.h"
#include "game/walkpathfindingcomponent.h"
#include "game/effectspritecomponent.h"
#include "game/soldier.h"
#include "game/gameplayer.h"

#include <sstream>
#include <iomanip>


class ImaginaWars : public Game
{
public:

    ImaginaWars(int _fps = 60);
    virtual ~ImaginaWars();

    void startGame() override;

    GamePlayer *getPlayer1();
    GamePlayer *getPlayer2();

protected:

    void initShaders() override;
    void initTextures() override;

    void mouseReleaseEvent(QMouseEvent *e) override;


    void loadUnitTextures(std::string name);
    void loadAnimTextures(std::string unitName, std::string animName, std::string animPrefix);


    GameMap *gm;
    Soldier *spr;

    GamePlayer *player1 = new GamePlayer(GamePlayer::TYPE_HUMAN, 0), *player2 = new GamePlayer(GamePlayer::TYPE_AI, 1);
};

#endif // IMAGINAWARS_H
