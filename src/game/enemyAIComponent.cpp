
#include "game/enemyAIComponent.h"

#include <game/gamemap.h>
#include <game/imaginawars.h>


EnemyAIComponent::EnemyAIComponent(GamePlayer *p)
{
    player = p;
    gameMap = ((ImaginaWars *)ImaginaWars::getInstance())->getGameMap();

    rnd.seed(std::random_device()());

    //std::uniform_int_distribution<std::mt19937::result_type> dist100(1,100);
    //std::cout << dist100(rnd) << std::endl;
}

void EnemyAIComponent::update()
{

}

void EnemyAIComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;


    if(cptFrames % 60 == 0 && gameMap->getIsInitialized() /*&& gameMap->getWidth() > 0*/)
    {
        //qDebug() << "AI ENEMY";
        //qDebug() << gameMap->getWidth();

        std::uniform_int_distribution<std::mt19937::result_type> dist100(0,99);
        std::uniform_int_distribution<std::mt19937::result_type> dist002(0,1);

        int r1001 = dist100(rnd);
        int r1002 = dist100(rnd);
        int r1003 = dist100(rnd);
        int r1004 = dist100(rnd);

        int r0021 = dist002(rnd);
        int r0022 = dist002(rnd);
        int r0023 = dist002(rnd);
        int r0024 = dist002(rnd);


        if(r1001 < 10) {

            player->getBuilding(r0021)->NextBuilding();
        }

        else if(r1001 < 50)
        {
            /*if(r1002 < 25) player->tryMoveTarget(r0021, 0, 1, gameMap);
            else if(r1002 < 50) player->tryMoveTarget(r0021, 0, -1, gameMap);
            else if(r1002 < 75) player->tryMoveTarget(r0021, 1, 0, gameMap);
            else player->tryMoveTarget(r0021, -1, 0, gameMap);*/
        }

     }


    ++cptFrames;
}
