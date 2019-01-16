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


    // création du sprite et component pour la gestion de la vie
    if(lifeSprite == NULL)
    {
        if(player->getNumPlayer() == 0) lifeSprite = new Sprite("lifered", QVector3D(0, 0, 0.1), 0, QVector2D(0.04, 0.007), sprite->getShader());
        else lifeSprite = new Sprite("lifeorange", QVector3D(0, 0, 0.1), 0, QVector2D(0.04, 0.007), sprite->getShader());

        lifeSprite->createGeometry();
        lifeSprite->addComponent(new LifeBuildingComponent(this, sprite));

        GameScene::getInstance()->addChild(lifeSprite);
    }


    if(cptFrames % turnDuration == (turnDuration - 1) && life > 0) // seulement toutes les x secondes : on génére une unité
    {
        //qDebug() << "GENERATE UNIT " << type << " - " << QString(player->getName().c_str());

        //if(player->getNumPlayer() == 1) return; // pour cheater :o

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
    if(life <= 0) return;

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

Sprite *BuildingComponent::getSprite() const
{
    return sprite;
}



GamePlayer *BuildingComponent::getPlayer() const
{
    return player;
}

int BuildingComponent::getLife() const
{
    return life;
}

void BuildingComponent::setLife(int value)
{
    if(life <= 0) return; // éviter de casser plusieurs fois

    if (value <= 0)
    {
        life = 0;
        kc();
    }

    else life = value;
}


void BuildingComponent::kc()
{
    qDebug() << "BUILDING DESTROYED";


    ((ImaginaWars*)ImaginaWars::getInstance())->unregisterBuilding(this); // on doit supprimer de la liste AVANT de supprimer l'objet

    sprite->setLocalRotation(QQuaternion::fromEulerAngles(QVector3D(0,0,180)));
    sprite->setLocalPosition(sprite->getLocalPosition() + QVector3D(0,-0.3,-0.01));
    sprite->setLocalScale(QVector3D(0.1,0.06,0.1));

    ResourcesManager::getInstance()->getGameSound("boom")->play();


    // condition de victoire = détruire un seul ou tous les bâtiments ?
    // à voir ce qui est le plus intéressant pour le gameplay et la stratégie
    // pour le moment : un seul, il faut donc défendre ses 2 bâtiments

    if(!player->isHuman()) ((ImaginaWars*)Game::getInstance())->win();
    else ((ImaginaWars*)Game::getInstance())->lose();
}

