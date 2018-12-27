#ifndef GAMEMAP_H
#define GAMEMAP_H


#include <qdebug.h>
#include <qstring.h>
#include <qfile.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "engine/sprite.h"


class GameMap : public GameObject
{
public:
    GameMap(QString path);
protected:

};

#endif // GAMEMAP_H
