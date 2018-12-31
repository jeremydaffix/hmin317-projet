#ifndef WALKPATHFINDINGCOMPONENT_H
#define WALKPATHFINDINGCOMPONENT_H


#include "gamemap.h"

#include <engine/gameobject.h>



class WalkPathfindingComponent : public Component
{
public:
    WalkPathfindingComponent(GameMap *gm);

    void update();
    void fixedUpdate();

protected:

    //QVector2D direction;
    std::list<QVector2D> path;
    GameMap *gameMap;
};


#endif // WALKPATHFINDINGCOMPONENT_H
