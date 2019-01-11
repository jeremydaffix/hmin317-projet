#include "buildingcomponent.h"


int BuildingComponent::turnDuration = 5 * 60;


BuildingComponent::BuildingComponent(BuildingComponent::TYPE_BUILDING t, GamePlayer *p)
{
    type = t;

    player = p;

    //refreshTexture();
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
        //qDebug() << "GENERATE UNIT " << type << " - " << QString(player->getName().c_str());
    }


    ++cptFrames;
}

void BuildingComponent::NextBuilding()
{
    type = (TYPE_BUILDING) ((type + 1) % TYPE_BUILDING_LENGTH);

    refreshTexture(); // change la texture en fonction du nouveau type de bâtiment
}

void BuildingComponent::refreshTexture()
{
    if(sprite != NULL) switch(type)
    {

    case TYPE_KNIGHT:
        sprite->setTexture(ResourcesManager::getInstance()->getGameTexture("building_knight"));
        break;

    case TYPE_HORSE:
        sprite->setTexture(ResourcesManager::getInstance()->getGameTexture("building_horse"));
        break;

    case TYPE_ARCHER:
        sprite->setTexture(ResourcesManager::getInstance()->getGameTexture("building_archer"));
        break;

    case TYPE_TECHNO:
        sprite->setTexture(ResourcesManager::getInstance()->getGameTexture("building_techno"));
        break;

    case TYPE_TOWER:
        sprite->setTexture(ResourcesManager::getInstance()->getGameTexture("building_tower"));
        break;

    default:
        break;
    }
}

