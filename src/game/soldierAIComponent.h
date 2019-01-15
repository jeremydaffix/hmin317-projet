
#ifndef SOLDIERAICOMPONENT_H
#define SOLDIERAICOMPONENT_H

#include <QtMultimedia/QSoundEffect>

#include <engine/component.h>
//#include <game/imaginawars.h>
//#include <game/soldier.h>

class Soldier;
class ImaginaWars;


// classe de composant représentant l'intelligence de combat d'un soldat :
// attaquer un soldat ennemi proche, lui infliger des dégâts,...

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

    QSoundEffect qse; // pour pouvoir faire jouer le même qse par plusieurs soldats en même temps

};

#endif // SOLDIERAICOMPONENT_H
