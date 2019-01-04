#include "soldier.h"

#include <game/walkpathfindingcomponent.h>


Soldier::Soldier(TYPE_SOLDIER t, GameMap *gm, QOpenGLTexture *tex, QVector3D pos, float rot, QVector2D sc, QOpenGLShaderProgram *sh) : Sprite(tex, pos, rot, sc, sh)
{
    type = t;
    string name = "";



    if(type == TYPE_KNIGHT) name = "knight";


    // création component pour le pathfinding

    pathfinding = new WalkPathfindingComponent(gm);
    addComponent(pathfinding);


    // création components d'animation

    CREATE_ANIM_GEN(walk, w, 15)
    CREATE_ANIM_GEN(looking, l, 10)


    currentState = STATE_LOOKING_S;

    selectAnim();
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

    SpriteAnimationComponent * anim = new SpriteAnimationComponent(speed);

    anim->setEnabled(false);

    for(int i = 0 ; i < 12 ; ++i)
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

// générer ???



void Soldier::selectAnim()
{
    DISABLE_ANIM_GEN(walk)
    DISABLE_ANIM_GEN(looking)

    SELECT_ANIM_GEN(WALK, walk)
    SELECT_ANIM_GEN(LOOKING, looking)
}

