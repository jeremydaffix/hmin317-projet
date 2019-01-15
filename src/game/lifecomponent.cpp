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

    float w = 0.04 * life / 100;

    sprite->setLocalPosition(soldier->getLocalPosition() + QVector3D(0 , 0.30, 0));
    //sprite->setLocalPosition(soldier->getLocalPosition() + QVector3D( - ((0.04 - w) / 2.) ,0.30, 0));
    sprite->setLocalScale(QVector2D(w, 0.007));

    if(cptFrames % (60) == 0) soldier->setLife(life - 3); // malus toutes les s

    ++cptFrames;
}
