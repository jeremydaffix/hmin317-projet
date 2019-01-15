#ifndef WALKPATHFINDINGCOMPONENT_H
#define WALKPATHFINDINGCOMPONENT_H


#include "gamemap.h"

#include <engine/gameobject.h>
#include <game/soldier.h>


class WalkPathfindingComponent : public Component
{
public:
    WalkPathfindingComponent(GameMap *gm);

    void update();
    void fixedUpdate();

    QVector2D getTargetPos() const;
    void setTargetPos(const QVector2D &value);

protected:

    //QVector2D direction;
    std::list<QVector2D> path;
    GameMap *gameMap;
    QVector2D targetPos;
    Soldier *soldier = NULL;
    ImaginaWars *iw = NULL;

    bool isPosFree(QVector3D pos);
    void moveTowards(QVector2D dir);
};


#endif // WALKPATHFINDINGCOMPONENT_H
