#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H


#include <string>

#include <qstring.h>
#include <qvector2d.h>

#include <game/effectspritecomponent.h>
//#<include <game/buildingcomponent.h>
//#include <game/gamemap.h>


class BuildingComponent;
class GameMap;

class GamePlayer
{
public:

    enum TYPE_PLAYER {

        TYPE_HUMAN, // joueur manette / clavier
        TYPE_AI // ordinateur
        // idée : ajouter plusieurs types d'AI ? (difficulté, style de jeu défensif ou agressif,...)
    };


    GamePlayer(TYPE_PLAYER t, int n);

    std::string getName();

    BuildingComponent *getBuilding(int i) const;
    void setBuilding(int i, BuildingComponent *value);

    QVector2D getPosTarget(int i) const;
    void setPosTarget(int i, const QVector2D &value);

    QVector2D tryMoveTarget(int i, int x, int y, GameMap *gm);

    int getNumPlayer() const;
    void setNumPlayer(int value);

protected:

    int numPlayer;
    TYPE_PLAYER type;

    QVector2D posTarget[2];
    BuildingComponent *building[2];

};

#endif // GAMEPLAYER_H
