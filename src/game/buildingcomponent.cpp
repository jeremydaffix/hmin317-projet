#include "buildingcomponent.h"


int BuildingComponent::turnDuration = 5 * 60;


BuildingComponent::BuildingComponent(BuildingComponent::TYPE_BUILDING t, GamePlayer *p)
{
    type = t;

    player = p;
}



void BuildingComponent::update()
{

}

void BuildingComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;

    sprite = (Sprite*)getContainer();

    if(cptFrames % turnDuration == (turnDuration - 1))
    {
        qDebug() << "GENERATE UNIT " << type << " - " << QString(player->getName().c_str());
    }


    ++cptFrames;
}

