#include "buildingcomponent.h"


#include <game/soldier.h>
#include <game/imaginawars.h>


int BuildingComponent::turnDuration = 5 * 60;


BuildingComponent::BuildingComponent(BuildingComponent::TYPE_BUILDING t, int i, GamePlayer *p, GameMap *gm)
{
    type = t;

    player = p;

    gameMap = gm;

    id = i;

    //refreshTexture();

    ((ImaginaWars*)ImaginaWars::getInstance())->registerBuilding(this);
}

BuildingComponent::~BuildingComponent()
{
    ((ImaginaWars*)ImaginaWars::getInstance())->unregisterBuilding(this);
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

        int decal = player->getNumPlayer() == 0 ? -0.8 : 1.5;
        Soldier *soldier;

        if(type == TYPE_KNIGHT)
        {
             soldier = new Soldier(Soldier::TYPE_KNIGHT, player, gameMap, player->getPosTarget(id), NULL,
                                         QVector2D(sprite->getLocalPosition().x() + decal, sprite->getLocalPosition().y() + 0.5),
                                         0,
                                         QVector2D(0.055, 0.055),
                                         ResourcesManager::getInstance()->getGameShader("texturetoon"));

             GameScene::getInstance()->addChild(soldier);

        }

        else if(type == TYPE_FAIRY)
        {
             soldier = new Soldier(Soldier::TYPE_FAIRY, player, gameMap, player->getPosTarget(id), NULL,
                                         QVector2D(sprite->getLocalPosition().x() +  decal, sprite->getLocalPosition().y() + 0.5),
                                         0,
                                         QVector2D(0.070, 0.070),
                                         ResourcesManager::getInstance()->getGameShader("texturetoon"));

             GameScene::getInstance()->addChild(soldier);

        }

        else if(type == TYPE_ARCHER)
        {
             soldier = new Soldier(Soldier::TYPE_ARCHER, player, gameMap, player->getPosTarget(id), NULL,
                                         QVector2D(sprite->getLocalPosition().x() +  decal, sprite->getLocalPosition().y() + 0.5),
                                         0,
                                         QVector2D(0.070, 0.070),
                                         ResourcesManager::getInstance()->getGameShader("texturetoon"));

             GameScene::getInstance()->addChild(soldier);

        }

        else {


        }

        //cptFrames = -99999; // debug
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

    case TYPE_FAIRY:
        sprite->setTexture(ResourcesManager::getInstance()->getGameTexture("building_fairy"));
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

int BuildingComponent::getLife() const
{
    return life;
}

void BuildingComponent::setLife(int value)
{
    life = value;
}
