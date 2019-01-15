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
    //((ImaginaWars*)ImaginaWars::getInstance())->unregisterBuilding(this); // pas besoin car supprimé par graph de scene
}



void BuildingComponent::update()
{

}

void BuildingComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;

    sprite = (Sprite*)getContainer();

    if(cptFrames % turnDuration == (turnDuration - 1)) // seulement toutes les x secondes : on génére une unité
    {
        //qDebug() << "GENERATE UNIT " << type << " - " << QString(player->getName().c_str());

        int decal = player->getNumPlayer() == 0 ? -0.8 : 1.5; // pour ne pas poper sur le bâtiment
        Soldier *soldier;

        if(type == TYPE_KNIGHT) // création fantassin
        {
             soldier = new Soldier(Soldier::TYPE_KNIGHT, player, gameMap, player->getPosTarget(id), NULL,
                                         QVector3D(sprite->getLocalPosition().x() + decal, sprite->getLocalPosition().y() + 0.5, 0.02),
                                         0,
                                         QVector2D(0.055, 0.055),
                                         ResourcesManager::getInstance()->getGameShader("texturetoon"));

             GameScene::getInstance()->addChild(soldier);

        }

        else if(type == TYPE_FAIRY) // création fée
        {
             soldier = new Soldier(Soldier::TYPE_FAIRY, player, gameMap, player->getPosTarget(id), NULL,
                                         QVector3D(sprite->getLocalPosition().x() +  decal, sprite->getLocalPosition().y() + 0.5, 0.02),
                                         0,
                                         QVector2D(0.070, 0.070),
                                         ResourcesManager::getInstance()->getGameShader("texturetoon"));

             GameScene::getInstance()->addChild(soldier);

        }

        else if(type == TYPE_ARCHER) // création archer
        {
             soldier = new Soldier(Soldier::TYPE_ARCHER, player, gameMap, player->getPosTarget(id), NULL,
                                         QVector3D(sprite->getLocalPosition().x() +  decal, sprite->getLocalPosition().y() + 0.5, 0.02),
                                         0,
                                         QVector2D(0.060, 0.060),
                                         ResourcesManager::getInstance()->getGameShader("texturetoon"));

             GameScene::getInstance()->addChild(soldier);

        }

        else { // TODO : gérer ici les autres bâtiments (tours, bâtiments technologiques,...)


        }

        ResourcesManager::getInstance()->getGameSound("interface4")->play();

        //cptFrames = -99999; // debug
    }


    ++cptFrames;
}

void BuildingComponent::NextBuilding() // sélectionner le prochain type de bâtiment
{
    //type = (TYPE_BUILDING) ((type + 1) % TYPE_BUILDING_LENGTH);
    type = (TYPE_BUILDING) ((type + 1) % 3); // pour le moment on ne gère pas bâtiment technologique et tour de garde

    refreshTexture(); // change la texture en fonction du nouveau type de bâtiment
}

void BuildingComponent::refreshTexture() // sélectionner et afficher la bonne texture du bâtiment selon son type
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

