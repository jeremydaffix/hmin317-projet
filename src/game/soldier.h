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


class Soldier : public Sprite
{
public:

    static const int TYPE_KNIGHT = 0;
    static const int TYPE_HORSE = 1;
    static const int TYPE_ARCHER = 2;


    Soldier(int t, GameMap *gm, QOpenGLTexture *tex, QVector3D pos = QVector3D(), float rot = 0, QVector2D sc = QVector2D(1, 1), QOpenGLShaderProgram* sh = NULL);

    WalkPathfindingComponent *getPathfinding() const;

    int getType() const;

    void selectAnimWalk(QVector2D dir);


protected:

    SpriteAnimationComponent *idle,
                             *walkN, *walkNE, *walkE, *walkSE, *walkS, *walkSW, *walkW, *walkNW;
    WalkPathfindingComponent *pathfinding;
    int type;

    SpriteAnimationComponent *createAnim(string name);
};

#endif // SOLDIER_H
