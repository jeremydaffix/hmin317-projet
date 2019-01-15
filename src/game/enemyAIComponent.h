
#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H

#include <random>

#include <engine/component.h>

class GamePlayer;
class GameMap;


// classe contenant l'AI de l'ennemi
// il sera possible de faire plusieurs classes
// pour différentes stratégies de jeu
// principe :
// toutes les x secondes (fixedUpdate),
// on va choisir une action à réaliser
// en fonction du hasard et du contexte
// et on "simule" l'appui du joueur sur une touche
// le reste est géré de la même manière que le joueur humain, de façon générique


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

    std::mt19937 rnd; // pour nombres aléatoires
};

#endif // ENEMYAICOMPONENT_H
