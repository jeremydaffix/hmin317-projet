#ifndef BUILDING_H
#define BUILDING_H

#include <engine/sprite.h>
#include <game/gameplayer.h>
//#include <game/imaginawars.h>
//#include <game/soldier.h>

// classe componsant pour les bâtiments
// en fonction du type de bâtiment (knight, archer, fée) sélectionné,
// une unité est générée tous les 5s

class BuildingComponent : public Component
{
public:

    // types de bâtiments possibles
    enum TYPE_BUILDING {

        TYPE_KNIGHT, // fantassin, fort contre archers
        TYPE_FAIRY, // fée (unité volante), forte contre fantassins
        TYPE_ARCHER, // archer, fort contre fée
        TYPE_TECHNO, // pas implémenté : bâtiment technologique
        TYPE_TOWER, // pas implémenté : tour de défense
        TYPE_BUILDING_LENGTH
    };

    BuildingComponent(TYPE_BUILDING t, int i, GamePlayer *p, GameMap *gm);
    virtual ~BuildingComponent();


    void update();
    void fixedUpdate();

    void NextBuilding();

    // vie du bâtiment à 0 = on le détruit
    // but = détruire les bâtiments adverses
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
