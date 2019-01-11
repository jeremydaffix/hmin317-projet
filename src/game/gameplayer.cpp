#include "gameplayer.h"


GamePlayer::GamePlayer(GamePlayer::TYPE_PLAYER t, int n)
{
    type = t;
    numPlayer = n;


    if(type == TYPE_HUMAN)
    {
        // add component
    }

    else if(type == TYPE_AI)
    {

    }
}

std::string GamePlayer::getName()
{
    std::string ret = "PLAYER" + std::to_string(numPlayer + 1);

    return ret;
}
