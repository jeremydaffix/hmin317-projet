#include "soldier.h"

#include <game/walkpathfindingcomponent.h>


Soldier::Soldier(int t, GameMap *gm, QOpenGLTexture *tex, QVector3D pos, float rot, QVector2D sc, QOpenGLShaderProgram *sh) : Sprite(tex, pos, rot, sc, sh)
{
    type = t;
    string name = "";

    if(type == TYPE_KNIGHT) name = "knight";


    // création component pour le pathfinding

    pathfinding = new WalkPathfindingComponent(gm);
    addComponent(pathfinding);


    // création components d'animation

    walkN = createAnim(name + "_w_n_");
    walkNE = createAnim(name + "_w_ne_");
    walkE = createAnim(name + "_w_e_");
    walkSE = createAnim(name + "_w_se_");
    walkS = createAnim(name + "_w_s_");
    walkSW = createAnim(name + "_w_sw_");
    walkW = createAnim(name + "_w_w_");
    walkNW = createAnim(name + "_w_nw_");


    walkS->setEnabled(true);
}

WalkPathfindingComponent *Soldier::getPathfinding() const
{
    return pathfinding;
}

int Soldier::getType() const
{
    return type;
}

SpriteAnimationComponent *Soldier::createAnim(string name)
{
    int speed = 15;

    SpriteAnimationComponent * anim = new SpriteAnimationComponent(speed);

    anim->setEnabled(false);

    for(int i = 0 ; i < 12 ; ++i)
    {
        anim->addTexture(ResourcesManager::getInstance()->getGameTexture(name + std::to_string(i)));
    }

    addComponent(anim);

    return anim;
}

void Soldier::selectAnimWalk(QVector2D dir)
{
    walkN->setEnabled(false);
    walkNE->setEnabled(false);
    walkE->setEnabled(false);
    walkSE->setEnabled(false);
    walkS->setEnabled(false);
    walkSW->setEnabled(false);
    walkW->setEnabled(false);
    walkNW->setEnabled(false);


    double rad = std::atan2(dir.x(), dir.y());
    double deg = (rad / M_PI) * 180.0;

    qDebug() << "angle " << deg;

    if(deg >=-22.5 && deg < 22.5) walkN->setEnabled(true);
    else if(deg >= 22.5 && deg < 67.5) walkNE->setEnabled(true);
    else if(deg >= 67.5 && deg < 112.5) walkE->setEnabled(true);
    else if(deg >= 112.5 && deg < 158.0) walkSE->setEnabled(true);

    else if(deg >= -67.5 && deg < -22.5) walkNW->setEnabled(true);
    else if(deg >= -112.5 && deg < -67.5) walkW->setEnabled(true);
    else if(deg >= -158.0 && deg < -112.5) walkSW->setEnabled(true);
    else walkS->setEnabled(true);
}
