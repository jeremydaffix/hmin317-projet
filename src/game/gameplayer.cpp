#include "gameplayer.h"


#include <game/gamemap.h>


GamePlayer::GamePlayer(GamePlayer::TYPE_PLAYER t, int n)
{
    type = t;
    numPlayer = n;

    posTarget[0] = QVector2D(12, 4);
    posTarget[1] = QVector2D(12, 6);


    if(type == TYPE_HUMAN)
    {
        // add component
    }

    else if(type == TYPE_AI)
    {

    }
}

std::string GamePlayer::getName()
{
    std::string ret = "PLAYER" + std::to_string(numPlayer + 1);

    return ret;
}



BuildingComponent *GamePlayer::getBuilding(int i) const
{
    return building[i];
}

void GamePlayer::setBuilding(int i, BuildingComponent *value)
{
    building[i] = value;
}

QVector2D GamePlayer::getPosTarget(int i) const
{
    return posTarget[i];
}

void GamePlayer::setPosTarget(int i, const QVector2D &value)
{
    posTarget[i] = value;
}


QVector2D GamePlayer::tryMoveTarget(int i, int x, int y, GameMap *gm)
{

    QVector2D currentCase = /*gm->posToCase*/(posTarget[i]);

    //qDebug() << currentCase << " " << gm->caseToPos(currentCase) << " " << gm->posToCase(gm->caseToPos(currentCase));

    int cx = (int)currentCase.x();
    int cy = (int)currentCase.y();

    if((cx + x) >= 0 && (cx + x) < gm->getWidth())
    {
        if(gm->isWalkable(cx + x, cy)) cx += x;
    }

    if((cy + y) >= 0 && (cy + y) < gm->getHeight())
    {
        if(gm->isWalkable(cx, cy + y)) cy += y;
    }


    currentCase = QVector2D(cx, cy);

    posTarget[i] = currentCase;

    return gm->caseToPos(currentCase);
}

int GamePlayer::getNumPlayer() const
{
    return numPlayer;
}

void GamePlayer::setNumPlayer(int value)
{
    numPlayer = value;
}


