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

#include "engine/sprite.h"


class GameMap : public GameObject
{
public:
    GameMap(QString path);
protected:
    Sprite* addSprite(std::string name, int caseX, int caseY, int rot = 0);
    int width, height;
};

#endif // GAMEMAP_H
