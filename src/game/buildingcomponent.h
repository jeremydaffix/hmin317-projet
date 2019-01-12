#ifndef BUILDING_H
#define BUILDING_H

#include <engine/sprite.h>
#include <game/gameplayer.h>
//#include <game/imaginawars.h>
//#include <game/soldier.h>


class BuildingComponent : public Component
{
public:

    enum TYPE_BUILDING {

        TYPE_KNIGHT,
        TYPE_FAIRY,
        TYPE_ARCHER,
        TYPE_TECHNO,
        TYPE_TOWER,
        TYPE_BUILDING_LENGTH
    };

    BuildingComponent(TYPE_BUILDING t, int i, GamePlayer *p, GameMap *gm);
    virtual ~BuildingComponent();


    void update();
    void fixedUpdate();

    void NextBuilding();

    int getLife() const;
    void setLife(int value);

protected:

    void refreshTexture();


    Sprite *sprite = NULL;
    TYPE_BUILDING type;

    int cptFrames = 0;

    int id;

    GamePlayer *player;
    GameMap *gameMap;

    int life = 500;


    static int turnDuration; // x seconds per turn
};

#endif // BUILDING_H
