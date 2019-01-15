#ifndef HUMANPLAYERCOMPONENT_H
#define HUMANPLAYERCOMPONENT_H

#include <engine/sprite.h>
#include <game/gameplayer.h>

#include <QtCore/QObject>
#include <QtCore/QTimer>


// cette classe de composant représente un joueur humain
// non utilisée pour le moment, elle sera utile pour
// l'utilisation des contrôles manettes

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
