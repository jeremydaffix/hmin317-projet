#ifndef HUMANPLAYERCOMPONENT_H
#define HUMANPLAYERCOMPONENT_H

#include <engine/sprite.h>
#include <game/gameplayer.h>

#include <QtCore/QObject>
#include <QtCore/QTimer>


class HumanPlayerComponent : public Component
{
public:
    HumanPlayerComponent(GamePlayer *p);

    void update();
    void fixedUpdate();

protected:

    GamePlayer *player = NULL;
    //QGamepad *gamepad;
};

#endif // HUMANPLAYERCOMPONENT_H
