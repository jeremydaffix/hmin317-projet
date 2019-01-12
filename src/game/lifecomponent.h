#ifndef LIFECOMPONENT_H
#define LIFECOMPONENT_H

#include <engine/sprite.h>
#include <engine/component.h>

class Soldier;

class LifeComponent : public Component
{
public:
    LifeComponent(Soldier *s);

    void update();
    void fixedUpdate();

protected:

    Sprite *sprite = NULL;
    Soldier *soldier = NULL;

    int cptFrames = 0;
};

#endif // LIFECOMPONENT_H
