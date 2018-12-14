#ifndef MOVINGCUBECOMPONENT_H
#define MOVINGCUBECOMPONENT_H

#include <engine/gameobject.h>


// Component pour faire bouger une balle.
class MovingBallComponent : public Component
{
public:
    MovingBallComponent();

    void update();
    void fixedUpdate();

protected:

    QVector2D direction;
};

#endif // MOVINGCUBECOMPONENT_H
