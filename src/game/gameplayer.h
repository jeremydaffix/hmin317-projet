#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H


#include <string>

#include <qstring.h>
#include <qvector2d.h>

#include <game/effectspritecomponent.h>
//#<include <game/buildingcomponent.h>
//#include <game/gamemap.h>
#include <game/enemyAIComponent.h>


class BuildingComponent;
class GameMap;

// classe représentant un joueur
// il peut s'agir d'un joueur humain ou d'une AI

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

    // ses bâtiments
    BuildingComponent *getBuilding(int i) const;
    void setBuilding(int i, BuildingComponent *value);

    // ses cibles
    QVector2D getPosTarget(int i) const;
    void setPosTarget(int i, const QVector2D &value);

    // essayer de bouger une des targets
    // (prend en compte les obstacles, on ne peut pas mettre la target sur un obstacle ou sortir de la map !)
    QVector2D tryMoveTarget(int i, int x, int y, GameMap *gm);

    // numéro de joueur unique
    int getNumPlayer() const;
    void setNumPlayer(int value);

    bool isHuman();

protected:

    int numPlayer;
    TYPE_PLAYER type;

    QVector2D posTarget[2];
    BuildingComponent *building[2];

    EnemyAIComponent *enemyAI; // composant ai ennemi
    GameObject enemyAIGO; // gameobject auquel attacher ce composant

};

#endif // GAMEPLAYER_H
