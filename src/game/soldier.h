#ifndef SOLDIER_H
#define SOLDIER_H

#include <qdebug.h>
#include <qstring.h>
#include <qfile.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cmath>

#include <engine/sprite.h>
#include <engine/spriteanimationcomponent.h>
//#include <game/walkpathfindingcomponent.h>
#include <game/gamemap.h>

class WalkPathfindingComponent;


// un peu de metaprogrammation pour éviter d'avoir à définir 8 états (pour 8 directions)
// pour chaque type d'animation :)

#define STATE_ANIM_GEN(stateName) \
    STATE_##stateName##_N, \
    STATE_##stateName##_NE, \
    STATE_##stateName##_E, \
    STATE_##stateName##_SE, \
    STATE_##stateName##_S, \
    STATE_##stateName##_SW, \
    STATE_##stateName##_W, \
    STATE_##stateName##_NW

#define CREATE_ANIM_GEN(animName, animPrefix, speed) \
    animName##N = createAnim(name + "_" + #animPrefix + "_n_", speed); \
    animName##NE = createAnim(name + "_" + #animPrefix + "_ne_", speed); \
    animName##E = createAnim(name + "_" + #animPrefix + "_e_", speed); \
    animName##SE = createAnim(name + "_" + #animPrefix + "_se_", speed); \
    animName##S = createAnim(name + "_" + #animPrefix + "_s_", speed); \
    animName##SW = createAnim(name + "_" + #animPrefix + "_sw_", speed); \
    animName##W = createAnim(name + "_" + #animPrefix + "_w_", speed); \
    animName##NW = createAnim(name + "_" + #animPrefix + "_nw_", speed);

#define DEF_ANIM_GEN(animName) \
    SpriteAnimationComponent *animName##N, *animName##NE, *animName##E, *animName##SE, *animName##S, *animName##SW, *animName##W, *animName##NW;

#define DISABLE_ANIM_GEN(animName) \
    animName##N->setEnabled(false); \
    animName##NE->setEnabled(false); \
    animName##E->setEnabled(false); \
    animName##SE->setEnabled(false); \
    animName##S->setEnabled(false); \
    animName##SW->setEnabled(false); \
    animName##W->setEnabled(false); \
    animName##NW->setEnabled(false);

#define SELECT_ANIM_GEN(stateName, animName) \
    if(currentState == STATE_##stateName##_N) animName##N->setEnabled(true); \
    if(currentState == STATE_##stateName##_NE) animName##NE->setEnabled(true); \
    if(currentState == STATE_##stateName##_E) animName##E->setEnabled(true); \
    if(currentState == STATE_##stateName##_SE) animName##SE->setEnabled(true); \
    if(currentState == STATE_##stateName##_S) animName##S->setEnabled(true); \
    if(currentState == STATE_##stateName##_SW) animName##SW->setEnabled(true); \
    if(currentState == STATE_##stateName##_W) animName##W->setEnabled(true); \
    if(currentState == STATE_##stateName##_NW) animName##NW->setEnabled(true);





class Soldier : public Sprite
{
public:

    enum TYPE_SOLDIER {

        TYPE_KNIGHT,
        TYPE_HORSE,
        TYPE_ARCHER
    };

    enum STATE_ANIM {

        STATE_ANIM_GEN(LOOKING),
        STATE_ANIM_GEN(WALK)
    };


    Soldier(TYPE_SOLDIER t, GameMap *gm, QOpenGLTexture *tex, QVector3D pos = QVector3D(), float rot = 0, QVector2D sc = QVector2D(1, 1), QOpenGLShaderProgram* sh = NULL);

    WalkPathfindingComponent *getPathfinding() const;

    TYPE_SOLDIER getType() const;

    void selectStateWalk(QVector2D dir);
    void selectStateLooking(QVector2D dir);

    void selectAnim();


protected:

    DEF_ANIM_GEN(walk)
    DEF_ANIM_GEN(looking)

    WalkPathfindingComponent *pathfinding;
    TYPE_SOLDIER type;

    SpriteAnimationComponent *createAnim(string name, int speed);

    STATE_ANIM currentState;
};

#endif // SOLDIER_H
