#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H


#include <string>


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

protected:

    int numPlayer;
    TYPE_PLAYER type;
};

#endif // GAMEPLAYER_H
