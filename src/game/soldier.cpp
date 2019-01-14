#include "soldier.h"

#include <game/walkpathfindingcomponent.h>
#include <game/imaginawars.h>


Soldier::Soldier(TYPE_SOLDIER t, GamePlayer *p, GameMap *gm, QVector2D goTo, QOpenGLTexture *tex, QVector3D pos, float rot, QVector2D sc, QOpenGLShaderProgram *sh) : Sprite(tex, pos, rot, sc, sh)
{
    type = t;
    player = p;
    string name = "";



    if(type == TYPE_KNIGHT) name = "knight";
    else if(type == TYPE_FAIRY) name = "fairy";
    else if(type == TYPE_ARCHER) name = "archer";


    // création component pour le pathfinding

    pathfinding = new WalkPathfindingComponent(gm);
    addComponent(pathfinding);

    pathfinding->setTargetPos(goTo);


    // création components d'animation

    CREATE_ANIM_GEN(walk, w, 15)
    CREATE_ANIM_GEN(looking, l, 10)
    CREATE_ANIM_GEN(attack, a, 10)


    currentState = STATE_LOOKING_S;

    selectAnim();





    if(player->getNumPlayer() == 0) lifeSprite = new Sprite("lifered", QVector3D(0, 0, 0.1), 0, QVector2D(0.04, 0.007), shader);
    else lifeSprite = new Sprite("lifeorange", QVector3D(0, 0, 0.1), 0, QVector2D(0.04, 0.007), shader);

    lifeSprite->createGeometry();
    //lifeSprite->addComponent(new DebugComponent());
    lifeSprite->addComponent(new LifeComponent(this));

    GameScene::getInstance()->addChild(lifeSprite);
    //addChild(lifeSprite);


    createGeometry();

    ((ImaginaWars*)ImaginaWars::getInstance())->registerSoldier(this);
}

Soldier::~Soldier()
{
    qDebug() << "DESTROYING SOLDIER";

    ((ImaginaWars*)ImaginaWars::getInstance())->unregisterSoldier(this);
}

WalkPathfindingComponent *Soldier::getPathfinding() const
{
    return pathfinding;
}

Soldier::TYPE_SOLDIER Soldier::getType() const
{
    return type;
}

SpriteAnimationComponent *Soldier::createAnim(string name, int speed)
{
    //int speed = 15;

    int nbrImgPerAnim = 0;
    if(type == TYPE_KNIGHT)
    {
        nbrImgPerAnim = 12;
    }

    else if(type == TYPE_FAIRY)
    {
        nbrImgPerAnim = 8;
        speed = (int)(speed * 0.75); // 8 images à la place de 12 #graphistes
    }

    else if(type == TYPE_ARCHER)
    {
        nbrImgPerAnim = 8;
        speed = (int)(speed * 0.70); // 8 images à la place de 12 #graphistes
    }

    SpriteAnimationComponent * anim = new SpriteAnimationComponent(speed);

    anim->setEnabled(false);

    for(int i = 0 ; i < nbrImgPerAnim ; ++i)
    {
        anim->addTexture(ResourcesManager::getInstance()->getGameTexture(name + std::to_string(i)));
    }

    addComponent(anim);

    return anim;
}

void Soldier::selectStateWalk(QVector2D dir)
{
    double rad = std::atan2(dir.x(), dir.y());
    double deg = (rad / M_PI) * 180.0;

    //qDebug() << "angle " << deg;

    if(deg >=-22.5 && deg < 22.5) currentState = STATE_WALK_N;
    else if(deg >= 22.5 && deg < 67.5) currentState = STATE_WALK_NE;
    else if(deg >= 67.5 && deg < 112.5) currentState = STATE_WALK_E;
    else if(deg >= 112.5 && deg < 158.0) currentState = STATE_WALK_SE;

    else if(deg >= -67.5 && deg < -22.5) currentState = STATE_WALK_NW;
    else if(deg >= -112.5 && deg < -67.5) currentState = STATE_WALK_W;
    else if(deg >= -158.0 && deg < -112.5) currentState = STATE_WALK_SW;
    else currentState = STATE_WALK_S;


    selectAnim();
}


void Soldier::selectStateLooking(QVector2D dir)
{
    double rad = std::atan2(dir.x(), dir.y());
    double deg = (rad / M_PI) * 180.0;

    //qDebug() << "angle " << deg;

    if(deg >=-22.5 && deg < 22.5) currentState = STATE_LOOKING_N;
    else if(deg >= 22.5 && deg < 67.5) currentState = STATE_LOOKING_NE;
    else if(deg >= 67.5 && deg < 112.5) currentState = STATE_LOOKING_E;
    else if(deg >= 112.5 && deg < 158.0) currentState = STATE_LOOKING_SE;

    else if(deg >= -67.5 && deg < -22.5) currentState = STATE_LOOKING_NW;
    else if(deg >= -112.5 && deg < -67.5) currentState = STATE_LOOKING_W;
    else if(deg >= -158.0 && deg < -112.5) currentState = STATE_LOOKING_SW;
    else currentState = STATE_LOOKING_S;


    selectAnim();
}


void Soldier::selectStateAttack(QVector2D dir)
{
    double rad = std::atan2(dir.x(), dir.y());
    double deg = (rad / M_PI) * 180.0;

    //qDebug() << "angle " << deg;

    if(deg >=-22.5 && deg < 22.5) currentState = STATE_ATTACK_N;
    else if(deg >= 22.5 && deg < 67.5) currentState = STATE_ATTACK_NE;
    else if(deg >= 67.5 && deg < 112.5) currentState = STATE_ATTACK_E;
    else if(deg >= 112.5 && deg < 158.0) currentState = STATE_ATTACK_SE;

    else if(deg >= -67.5 && deg < -22.5) currentState = STATE_ATTACK_NW;
    else if(deg >= -112.5 && deg < -67.5) currentState = STATE_ATTACK_W;
    else if(deg >= -158.0 && deg < -112.5) currentState = STATE_ATTACK_SW;
    else currentState = STATE_ATTACK_S;


    selectAnim();
}

// générer ???



void Soldier::selectAnim()
{
    DISABLE_ANIM_GEN(walk)
    DISABLE_ANIM_GEN(looking)
    DISABLE_ANIM_GEN(attack)

    SELECT_ANIM_GEN(WALK, walk)
    SELECT_ANIM_GEN(LOOKING, looking)
    SELECT_ANIM_GEN(ATTACK, attack)
}


int Soldier::getLife()
{
    return life;
}

void Soldier::setLife(int l)
{
    if (l <= 0)
    {
        life = 0;
        die();
    }

    else life = l;
}


void Soldier::die()
{
    qDebug("RIP");

    //destroy(); // suppression contenu (components et enfants)
    //GameScene::getInstance()->removeChild(this); // on enleve de la scene
    //delete this;
}

