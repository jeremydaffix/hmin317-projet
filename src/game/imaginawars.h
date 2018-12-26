#ifndef IMAGINAWARS_H
#define IMAGINAWARS_H

#include "engine/game.h"

#include <sstream>
#include <iomanip>


class ImaginaWars : public Game
{
public:

    ImaginaWars(int _fps = 60);

    void startGame();

protected:

    void initShaders();
    void initTextures();
};

#endif // IMAGINAWARS_H
