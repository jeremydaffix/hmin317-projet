
#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H

#include <random>

#include <engine/component.h>

class GamePlayer;
class GameMap;


class EnemyAIComponent : public Component
{
public:
    EnemyAIComponent(GamePlayer *p);

    void update();
    void fixedUpdate();

protected:

    int cptFrames = 0;

    GamePlayer *player;
    GameMap *gameMap;

    std::mt19937 rnd;
    //std::uniform_int_distribution<std::mt19937::result_type> dist100(1, 100); // distribution [1, 100]
};

#endif // ENEMYAICOMPONENT_H
