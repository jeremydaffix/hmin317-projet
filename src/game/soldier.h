#ifndef SOLDIER_H
#define SOLDIER_H

#include <qdebug.h>
#include <qstring.h>
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
#include <game/debugcomponent.h>
#include <game/lifecomponent.h>
#include <game/soldierAIComponent.h>

class WalkPathfindingComponent;


// classe gameobject représentant un soldat
// il peut être de différents types (fantassin, archer, fée)
// les différents components lui sont attachés :
// pathfinding, gestion de l'intelligence de combat, animations,...




// un peu de metaprogrammation pour éviter d'avoir à définir 8 états (pour 8 directions)
// pour chaque type d'animation :)
// pour économiser PLEIN de lignes de code à copier / coller !

// pour les états d'une animation (walking north, walking south,...)
#define STATE_ANIM_GEN(stateName) \
    STATE_##stateName##_N, \
    STATE_##stateName##_NE, \
    STATE_##stateName##_E, \
    STATE_##stateName##_SE, \
    STATE_##stateName##_S, \
    STATE_##stateName##_SW, \
    STATE_##stateName##_W, \
    STATE_##stateName##_NW

// pour la création des animations, de chaque côté
#define CREATE_ANIM_GEN(animName, animPrefix, speed) \
    animName##N = createAnim(name + "_" + #animPrefix + "_n_", speed); \
    animName##NE = createAnim(name + "_" + #animPrefix + "_ne_", speed); \
    animName##E = createAnim(name + "_" + #animPrefix + "_e_", speed); \
    animName##SE = createAnim(name + "_" + #animPrefix + "_se_", speed); \
    animName##S = createAnim(name + "_" + #animPrefix + "_s_", speed); \
    animName##SW = createAnim(name + "_" + #animPrefix + "_sw_", speed); \
    animName##W = createAnim(name + "_" + #animPrefix + "_w_", speed); \
    animName##NW = createAnim(name + "_" + #animPrefix + "_nw_", speed);

// pour définir les components (8 par type d'animation, donc)
#define DEF_ANIM_GEN(animName) \
    SpriteAnimationComponent *animName##N, *animName##NE, *animName##E, *animName##SE, *animName##S, *animName##SW, *animName##W, *animName##NW;


// pour désactiver toutes les animations d'un certain type
#define DISABLE_ANIM_GEN(animName) \
    animName##N->setEnabled(false); \
    animName##NE->setEnabled(false); \
    animName##E->setEnabled(false); \
    animName##SE->setEnabled(false); \
    animName##S->setEnabled(false); \
    animName##SW->setEnabled(false); \
    animName##W->setEnabled(false); \
    animName##NW->setEnabled(false);


// pour activer la bonne animation
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

    enum TYPE_SOLDIER { // type de soldat
        TYPE_KNIGHT,
        TYPE_FAIRY,
        TYPE_ARCHER
    };

    enum STATE_ANIM { // type pour l'état actuel de l'animation (exemple : marcher au nord)

        STATE_ANIM_GEN(LOOKING),
        STATE_ANIM_GEN(WALK),
        STATE_ANIM_GEN(ATTACK)
    };


    Soldier(TYPE_SOLDIER t, GamePlayer *p, GameMap *gm, QVector2D goTo, QOpenGLTexture *tex, QVector3D pos = QVector3D(), float rot = 0, QVector2D sc = QVector2D(1, 1), QOpenGLShaderProgram* sh = NULL);
    virtual ~Soldier();


    WalkPathfindingComponent *getPathfinding() const;

    TYPE_SOLDIER getType() const;

    void selectStateWalk(QVector2D dir); // choisir la bonne direction d'anim walk
    void selectStateLooking(QVector2D dir); // choisir la bonne direction d'anim idle
    void selectStateAttack(QVector2D dir); // choisir la bonne direction d'anim attack

    void selectAnim();

    void disableAnims();

    int getLife();
    void setLife(int l);

    void die(); // rip

    WalkPathfindingComponent *getPathfinding();
    GamePlayer *getPlayer();

protected:

    DEF_ANIM_GEN(walk)
    DEF_ANIM_GEN(looking)
    DEF_ANIM_GEN(attack)

    WalkPathfindingComponent *pathfinding;
    SoldierAIComponent *ai;

    TYPE_SOLDIER type;

    SpriteAnimationComponent *createAnim(string name, int speed); // pour créer un component d'animation d'un certain type (walk,...)

    STATE_ANIM currentState;

    GamePlayer *player;

    int life = 100;

    Sprite *lifeSprite;

    QSoundEffect qse; // pour pouvoir faire jouer le même qse par plusieurs soldats en même temps
};

#endif // SOLDIER_H
