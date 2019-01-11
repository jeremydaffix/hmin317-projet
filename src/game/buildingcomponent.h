#ifndef BUILDING_H
#define BUILDING_H

#include <engine/sprite.h>
#include <game/gameplayer.h>
//#include <game/imaginawars.h>


class BuildingComponent : public Component
{
public:

    enum TYPE_BUILDING {

        TYPE_KNIGHT,
        TYPE_HORSE,
        TYPE_ARCHER,
        TYPE_TECHNO,
        TYPE_TOWER,
        TYPE_BUILDING_LENGTH
    };

    BuildingComponent(TYPE_BUILDING t, GamePlayer *p);


    void update();
    void fixedUpdate();

    void NextBuilding();

protected:

    void refreshTexture();


    Sprite *sprite = NULL;
    TYPE_BUILDING type;

    int cptFrames = 0;

    GamePlayer *player;


    static int turnDuration; // x seconds per turn
};

#endif // BUILDING_H
