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

    QVector2D getTargetCase() const;
    void setTargetCase(const QVector2D &value);

protected:

    //QVector2D direction;
    std::list<QVector2D> path;
    GameMap *gameMap;
    QVector2D targetCase;
};


#endif // WALKPATHFINDINGCOMPONENT_H
