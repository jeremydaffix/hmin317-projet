#ifndef DEBUGCOMPONENT_H
#define DEBUGCOMPONENT_H

#include <engine/sprite.h>


class DebugComponent : public Component
{
public:
    DebugComponent();

    void update();
    void fixedUpdate();

protected:

    Sprite *sprite = NULL;

    int cptFrames = 0;
};

#endif // DEBUGCOMPONENT_H
