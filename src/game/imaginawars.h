#ifndef IMAGINAWARS_H
#define IMAGINAWARS_H

#include "engine/game.h"
#include "game/gamemap.h"
#include "game/walkpathfindingcomponent.h"
#include "game/effectspritecomponent.h"
#include "game/soldier.h"
#include "game/gameplayer.h"

#include <sstream>
#include <iomanip>


// classe principale du jeu
// hérite de Game et doit redéfinir certaines fonctions (initialisations,...)


class ImaginaWars : public Game
{
public:

    ImaginaWars(int _fps = 60);
    virtual ~ImaginaWars();

    void startGame() override;

    GamePlayer *getPlayer1();
    GamePlayer *getPlayer2();

    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;

    GameMap *getGameMap() const;

    void registerSoldier(Soldier *s);
    void registerBuilding(BuildingComponent *b);
    void unregisterSoldier(Soldier *s);
    void unregisterBuilding(BuildingComponent *b);


    // liste des soldats utilisée pour que les soldats ne se marchent pas dessus les uns les autres
    // + pour la détection d'ennemis
    std::list<Soldier *> getSoldiers() const;
    void setSoldiers(const std::list<Soldier *> &value);

    // liste des bâtiments utilisée pour détecter les bâtiments ennemis à proximité
    std::list<BuildingComponent *> getBuildings() const;
    void setBuildings(const std::list<BuildingComponent *> &value);

    void win(); // image gagnant
    void lose(); // image perdant

protected:

    void initShaders() override;
    void initTextures() override;

    void initSounds();

    void mouseReleaseEvent(QMouseEvent *e) override;


    //void loadUnitTextures(std::string name);
    void loadAnimTextures(std::string unitName, std::string animName, std::string animPrefix, int nbrImgPerAnim = 12, std::string zeros = "0");


    GameMap *gameMap;
    Soldier *spr;

    GamePlayer *player1 = new GamePlayer(GamePlayer::TYPE_HUMAN, 0), *player2 = new GamePlayer(GamePlayer::TYPE_AI, 1);

    Sprite *target1, *target2;

    std::list<Soldier *> soldiers;
    std::list<BuildingComponent *> buildings;
};

#endif // IMAGINAWARS_H
