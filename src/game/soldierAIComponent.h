
#ifndef SOLDIERAICOMPONENT_H
#define SOLDIERAICOMPONENT_H

#include <engine/component.h>
//#include <game/imaginawars.h>
//#include <game/soldier.h>

class Soldier;
class ImaginaWars;

class SoldierAIComponent : public Component
{
public:
    SoldierAIComponent(Soldier *s);

    void update();
    void fixedUpdate();

    protected:

    int cptFrames = 0;

    ImaginaWars *iw = NULL;
    Soldier *soldier;
};

#endif // SOLDIERAICOMPONENT_H
