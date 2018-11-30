#ifndef MOVINGCUBECOMPONENT_H
#define MOVINGCUBECOMPONENT_H

#include <gameobject.h>


// Component pour faire bouger un cube.
// EN COURS DE DEV
class MovingCubeComponent : public Component
{
public:
    MovingCubeComponent();

    void update();
    void fixedUpdate();
};

#endif // MOVINGCUBECOMPONENT_H
