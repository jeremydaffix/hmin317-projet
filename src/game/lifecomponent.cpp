#include "lifecomponent.h"

#include <game/soldier.h>


LifeComponent::LifeComponent(Soldier *s)
{
    soldier = s;
}

void LifeComponent::update()
{

}

void LifeComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;

    else if(sprite == NULL) sprite = (Sprite*)getContainer();


    int life = soldier->getLife();


    sprite->setLocalPosition(soldier->getLocalPosition() + QVector3D(0,0.30,0));
    sprite->setLocalScale(QVector2D(0.04 * life / 100, 0.007));

    if(cptFrames % (60 * 2) == 0) soldier->setLife(life - 1);

    ++cptFrames;
}
