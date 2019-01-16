#ifndef LIFEBUILDINGCOMPONENT_H
#define LIFEBUILDINGCOMPONENT_H

#include <engine/sprite.h>
#include <engine/component.h>

class BuildingComponent;

// classe de composant gérant la vie d'un bâtiment
// elle s'occupe du sprite d'affichage de la vie

class LifeBuildingComponent : public Component
{
public:
    LifeBuildingComponent(BuildingComponent *b, Sprite *bs);

    void update();
    void fixedUpdate();

protected:

    Sprite *sprite = NULL;
    BuildingComponent *building = NULL;
    Sprite *buildingSprite = NULL;

    int cptFrames = 0;
};

#endif // LIFEBUILDINGCOMPONENT_H
