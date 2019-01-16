#include "lifeBuildingComponent.h"

#include <game/buildingcomponent.h>


LifeBuildingComponent::LifeBuildingComponent(BuildingComponent *b, Sprite *bs)
{
    building = b;
    buildingSprite = bs;
}

void LifeBuildingComponent::update()
{

}

void LifeBuildingComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;

    else if(sprite == NULL) sprite = (Sprite*)getContainer();


    int life = building->getLife();

    float w = 0.015 * life / 100;

    sprite->setLocalPosition(buildingSprite->getLocalPosition() + QVector3D(0.5 , 1.20, 0));
    sprite->setLocalScale(QVector2D(w, 0.012));

    //if(cptFrames % (60) == 0) soldier->setLife(life - 3); // malus toutes les secondes

    ++cptFrames;
}
