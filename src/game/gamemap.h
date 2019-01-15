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
#include <iterator>
#include <algorithm>

#include "3rd/pathfinders.h"

#include "engine/sprite.h"
#include "game/buildingcomponent.h"
//#include <game/imaginawars.h>


// classe contenant la map du jeu
// chargement dans un fichier JSON
// puis on crée les sprites des tiles de la carte
// elle gère également la position des bâtiments de génération d'unités,
// le tableau des obstacles (utilisé pour le pathfinding)


class GameMap : public Model3D
{
public:
    GameMap(QString _path);
    virtual ~GameMap();
    void BuildMap();

    std::list<QVector2D> calcPath(QVector2D start, QVector2D target); // calcul du plus court chemin (A*)
    QVector2D posToCase(QVector2D pos); // transformation coordonnées world -> case
    QVector2D caseToPos(QVector2D cas); // transformation coordonnées case -> coordonnées world
    Sprite *getSprite(QVector2D pos);

    int getWidth() const; // largeur en cases
    int getHeight() const; // hauteur en cases

    bool isWalkable(int x, int y); // permet de savoir si il y a un obstacle sur une case ou non

    void HighlightTile(int, int x); // debug, permet d'illuminer temporairement une case

    bool getIsInitialized() const;

protected:
    Sprite* addSprite(std::string name, int caseX, int caseY, int rot = 0, float z = 0.00); // ajout d'un sprite de tile
    int width = 0, height = 0;
    QString path;
    unsigned char* walkableMap = NULL; // tableau avec les cases avec obstacles (0) et marchables (1)
    void initWalkableMap();
    bool isInitialized = false;
};

#endif // GAMEMAP_H
