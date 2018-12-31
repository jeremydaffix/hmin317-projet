#ifndef GAMEMAP_H
#define GAMEMAP_H


#include <qdebug.h>
#include <qstring.h>
#include <qfile.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>

#include <iostream>
#include <string>

#include "3rd/pathfinders.h"

#include "engine/sprite.h"
#include"engine/model3d.h"


class GameMap : public Model3D
{
public:
    GameMap(QString _path);
    virtual ~GameMap();
    void BuildMap();

    std::list<QVector2D> calcPath(QVector2D start, QVector2D target);
    QVector2D posToCase(QVector2D pos);
    QVector2D CaseToPos(QVector2D cas);

protected:
    Sprite* addSprite(std::string name, int caseX, int caseY, int rot = 0, float z = 0.00);
    int width, height;
    QString path;
    unsigned char* walkableMap = NULL;
    void initWalkableMap();
};

#endif // GAMEMAP_H
