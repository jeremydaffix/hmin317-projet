
#ifndef SOLDIERAICOMPONENT_H
#define SOLDIERAICOMPONENT_H

#include <engine/component.h>


class SoldierAIComponent : public Component
{
public:
    SoldierAIComponent();

    void update();
    void fixedUpdate();

    protected:

    int cptFrames = 0;
};

#endif // SOLDIERAICOMPONENT_H
