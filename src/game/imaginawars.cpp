#include "imaginawars.h"


/*

  TODO

  bug kill soldier ?

  petit generateur de code (gameobject)

  ameliorer pathfinding : zigzag (ou laisser ça donne un genre)

  component ennemyai
  IA ennemi

  gestion life (building)

  bonus random sur la map?

  integrer manette

  mode pvp (ultérieurement)


  ***

  ressources utilisées :

  http://www.reinerstilesets.de/graphics/2d-grafiken/2d-humans/ (public domain)
  https://kenney.nl/assets/medieval-rts (CC0 1.0 Universal)

  https://opengameart.org/content/battle-sound-effects (CC0)
  https://opengameart.org/content/battlecry (CC By 3.0)
  https://opengameart.org/content/rpg-sound-pack (CC0)
  https://opengameart.org/content/impact (CC0)
  https://opengameart.org/content/ghost (CC0)
  https://opengameart.org/content/rumbleexplosion (CC By 3.0)

  https://opengameart.org/content/battle-theme-a (CC0)

  https://github.com/quantumelixir/pathfinding

 */

ImaginaWars::ImaginaWars(int _fps) : Game(_fps)
{

}

ImaginaWars::~ImaginaWars()
{
    delete player1;
    delete player2;
}


void ImaginaWars::startGame()
{
    qDebug() << "IMAGINA WARS";

    // chargement et affichage de la carte + tableau des obstacles
    gameMap = new GameMap(":/resources/game/maps/test.json");
    gameMap->setLocalPosition(QVector3D(0.5,0.5,0));
    gameMap->setShader(ResourcesManager::getInstance()->getGameShader("texturedark")); // pour l'intégration graphique
    gameMap->BuildMap();
    GameScene::getInstance()->addChild(gameMap); // on ajoute tout ça au graph de scène


    player1->setPosTarget(0, QVector2D(7,9));
    player1->setPosTarget(1, QVector2D(7,5));

    //player2->setPosTarget(0, QVector2D(12, 4));
    //player2->setPosTarget(1, QVector2D(12, 6));

    player2->setPosTarget(0, QVector2D(18, 10));
    player2->setPosTarget(1, QVector2D(18, 2));

    // sprites pour les targets du joueur humain
    target1 = new Sprite("targetred1", QVector3D(gameMap->caseToPos(player1->getPosTarget(0))), 0, QVector2D(0.1,0.1));
    target2 = new Sprite("targetred2", QVector3D(gameMap->caseToPos(player1->getPosTarget(1))), 0, QVector2D(0.1,0.1));


    GameScene::getInstance()->addChild(target1);
    GameScene::getInstance()->addChild(target2);



    GameScene::getInstance()->createGeometry();
    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
    GameScene::getInstance()->setLocalPosition(QVector3D(0,0,15));


    // sons

    initSounds();

    ResourcesManager::getInstance()->getGameSound("battlecry")->play(); // un petit cri de guerre pour mettre dans l'ambiance

    // musique de fond

    ResourcesManager::getInstance()->playBackgroundMusic("qrc:/resources/sounds/battleThemeA.mp3"); // en boucle

}



void ImaginaWars::initShaders()
{
    QOpenGLShaderProgram * shaderTexture = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader.glsl");
    ResourcesManager::getInstance()->addGameShader("texture", shaderTexture);

    QOpenGLShaderProgram * shaderTextureToon = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_toon.glsl");
    ResourcesManager::getInstance()->addGameShader("texturetoon", shaderTextureToon);

    QOpenGLShaderProgram * shaderTextureDark = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_dark.glsl");
    ResourcesManager::getInstance()->addGameShader("texturedark", shaderTextureDark);

    QOpenGLShaderProgram * shaderTextureLight = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_light.glsl");
    ResourcesManager::getInstance()->addGameShader("texturelight", shaderTextureLight);

    GameScene::getInstance()->setDefaultShader(shaderTexture);
    //GameScene::getInstance()->setDefaultShader(shaderTextureToon);
}

void ImaginaWars::initTextures()
{
    QOpenGLTexture *textureDice = ResourcesManager::getInstance()->loadTexture(":/Resources/Textures/cube.png");
    ResourcesManager::getInstance()->addGameTexture("cube", textureDice);


    // textures units

    loadAnimTextures("knight", "walking", "w");
    loadAnimTextures("knight", "attack", "a");
    loadAnimTextures("knight", "looking", "l");
    loadAnimTextures("archer", "walking", "w", 9);
    loadAnimTextures("archer", "attack", "a", 9);
    loadAnimTextures("fairy", "walking", "w", 9);
    loadAnimTextures("fairy", "attack", "a", 9);


    // tiles

    int nbrTiles = 66;
    for(int i = 1 ; i <= nbrTiles ; ++i)
    {
        QString qs = ((i < 10 ? "0" : "") + std::to_string(i)).c_str();

        ResourcesManager::getInstance()->addGameTexture("medieval_tile_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/medievalrtspack/Tile/medievalTile_" + qs + ".png"));
    }

    // environnement

    int nbrEnv = 21;
    for(int i = 1 ; i <= nbrEnv ; ++i)
    {
        QString qs = ((i < 10 ? "0" : "") + std::to_string(i)).c_str();

        ResourcesManager::getInstance()->addGameTexture("medieval_env_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/medievalrtspack/Environment/medievalEnvironment_" + qs + ".png"));
    }


    // batiments

    ResourcesManager::getInstance()->addGameTexture("building_knight",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_17.png")));

    ResourcesManager::getInstance()->addGameTexture("building_fairy",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_19.png")));

    ResourcesManager::getInstance()->addGameTexture("building_archer",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_21.png")));

    ResourcesManager::getInstance()->addGameTexture("building_techno",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_20.png")));

    ResourcesManager::getInstance()->addGameTexture("building_tower",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_22.png")));


    GameScene::getInstance()->setDefaultTexture(textureDice);



    // custom

    ResourcesManager::getInstance()->addGameTexture("targetred1",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/targetred1.png")));

    ResourcesManager::getInstance()->addGameTexture("targetred2",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/targetred2.png")));

    ResourcesManager::getInstance()->addGameTexture("lifered",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/lifered.png")));


    ResourcesManager::getInstance()->addGameTexture("targetorange1",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/targetorange1.png")));

    ResourcesManager::getInstance()->addGameTexture("targetorange2",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/targetorange2.png")));

    ResourcesManager::getInstance()->addGameTexture("lifeorange",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/lifeorange.png")));


    ResourcesManager::getInstance()->addGameTexture("win",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/win.png")));

    ResourcesManager::getInstance()->addGameTexture("lose",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/custom/lose.png")));


    // fonts

   //ResourcesManager::getInstance()->addGameFont("arial", ResourcesManager::getInstance()->loadFont(":/resources/fonts/arial.ttf"));
    //ResourcesManager::getInstance()->addGameFont("gameover", ResourcesManager::getInstance()->loadFont(":/resources/fonts/Game-Over.ttf"));
}

void ImaginaWars::initSounds()
{
    ResourcesManager::getInstance()->addGameSound("battlecry",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/Battlecry.wav", 1.0));


    ResourcesManager::getInstance()->addGameSound("bow",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/battle_sound_effects_0/battle_sound_effects/Bow.wav"));

    ResourcesManager::getInstance()->addGameSound("swish2",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/battle_sound_effects_0/battle_sound_effects/swish_2.wav"));

    ResourcesManager::getInstance()->addGameSound("swish3",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/battle_sound_effects_0/battle_sound_effects/swish_3.wav"));

    ResourcesManager::getInstance()->addGameSound("swish4",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/battle_sound_effects_0/battle_sound_effects/swish_4.wav"));


    ResourcesManager::getInstance()->addGameSound("sword",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/battle/sword-unsheathe2.wav"));

    ResourcesManager::getInstance()->addGameSound("swing",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/battle/swing.wav"));

    ResourcesManager::getInstance()->addGameSound("spell",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/battle/spell.wav"));



    ResourcesManager::getInstance()->addGameSound("interface2",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/interface/interface2.wav"));

    ResourcesManager::getInstance()->addGameSound("interface4",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/interface/interface4.wav"));



    ResourcesManager::getInstance()->addGameSound("chainmail1",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/inventory/chainmail1.wav"));

    ResourcesManager::getInstance()->addGameSound("chainmail2",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rpg_sound_pack/RPG Sound Pack/inventory/chainmail2.wav"));


    ResourcesManager::getInstance()->addGameSound("ghost",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/ghost.wav"));

    ResourcesManager::getInstance()->addGameSound("boom",
                                                    ResourcesManager::getInstance()->loadSound("qrc:/resources/sounds/rumble.wav", 1.0));
}



/*void ImaginaWars::loadUnitTextures(std::string name)
{
    loadAnimTextures(name, "walking", "w");
    loadAnimTextures(name, "looking", "l");
}*/

void ImaginaWars::loadAnimTextures(std::string unitName, std::string animName, std::string animPrefix, int nbrImgPerAnim, std::string zeros)
{
    for(int i = 0 ; i < nbrImgPerAnim ; ++i)
    {
        std::string qs = ((i < 10 ? zeros : "") + std::to_string(i)).c_str();

        //qDebug() << (":/resources/textures/units/" + unitName + "/" + animName + " n00" + qs + ".png").c_str();
        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_n_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " n00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_ne_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " ne00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_e_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " e00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_se_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " se00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_s_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " s00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_sw_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " sw00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_w_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " w00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_nw_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/" + animName + " nw00" + qs + ".png")));
    }
}

std::list<BuildingComponent *> ImaginaWars::getBuildings() const
{
    return buildings;
}

void ImaginaWars::setBuildings(const std::list<BuildingComponent *> &value)
{
    buildings = value;
}



std::list<Soldier *> ImaginaWars::getSoldiers() const
{
    return soldiers;
}

void ImaginaWars::setSoldiers(const std::list<Soldier *> &value)
{
    soldiers = value;
}

GameMap *ImaginaWars::getGameMap() const
{
    return gameMap;
}

void ImaginaWars::registerSoldier(Soldier *s)
{
    soldiers.push_front(s);
}

void ImaginaWars::registerBuilding(BuildingComponent *b)
{
    buildings.push_front(b);
}

void ImaginaWars::unregisterSoldier(Soldier *s)
{
    auto pos = std::find(soldiers.begin(), soldiers.end(), s);
    if(pos != soldiers.end()) soldiers.erase(pos);
}

void ImaginaWars::unregisterBuilding(BuildingComponent *b)
{
    auto pos = std::find(buildings.begin(), buildings.end(), b);
    if(pos != buildings.end()) buildings.erase(pos);
}

GamePlayer *ImaginaWars::getPlayer2()
{
    return player2;
}



GamePlayer *ImaginaWars::getPlayer1()
{
    return player1;
}



void ImaginaWars::keyPressEvent(QKeyEvent *e)
{

}

void ImaginaWars::keyReleaseEvent(QKeyEvent *e)
{
    QVector3D newPos;

    if(e->key() == Qt::Key_Escape)
    {
        this->close();
    }

    // batiments
    switch(e->key())
    {
        case Qt::Key_1:
            player1->getBuilding(0)->NextBuilding();
            ResourcesManager::getInstance()->getGameSound("chainmail1")->play();
        break;

        case Qt::Key_2:
            player1->getBuilding(1)->NextBuilding();
            ResourcesManager::getInstance()->getGameSound("chainmail2")->play();
        break;

        default:
        break;
    }


    // target 1

    bool fxlight1 = false;
    bool fxdark1 = false;

    switch(e->key())
    {
        case Qt::Key_Up:
            newPos = player1->tryMoveTarget(0, 0, 1, gameMap);

            if(newPos != target1->getLocalPosition()) fxlight1 = true;
            else fxdark1 = true;

            target1->setLocalPosition(newPos);

        break;

        case Qt::Key_Down:
            newPos = player1->tryMoveTarget(0, 0, -1, gameMap);

            if(newPos != target1->getLocalPosition()) fxlight1 = true;
            else fxdark1 = true;

            target1->setLocalPosition(newPos);
        break;

        case Qt::Key_Left:
            newPos = player1->tryMoveTarget(0, -1, 0, gameMap);

            if(newPos != target1->getLocalPosition()) fxlight1 = true;
            else fxdark1 = true;

            target1->setLocalPosition(newPos);
        break;

        case Qt::Key_Right:
            newPos = player1->tryMoveTarget(0, 1, 0, gameMap);

            if(newPos != target1->getLocalPosition()) fxlight1 = true;
            else fxdark1 = true;

            target1->setLocalPosition(newPos);
        break;


        default:
        break;
    }

    if(fxlight1)
    {
        target1->addComponent(new EffectSpriteComponent(
                                       EffectSpriteComponent::TYPE_HIGHLIGHT, 60 * 0.15,
                                       ResourcesManager::getInstance()->getGameShader("texture"),
                                       ResourcesManager::getInstance()->getGameShader("texturelight")));

        ResourcesManager::getInstance()->getGameSound("swing")->play();
    }

    else if (fxdark1)
    {
        target1->addComponent(new EffectSpriteComponent(
                          EffectSpriteComponent::TYPE_HIGHLIGHT, 60 * 0.15,
                          ResourcesManager::getInstance()->getGameShader("texture"),
                          ResourcesManager::getInstance()->getGameShader("texturedark")));

        ResourcesManager::getInstance()->getGameSound("interface2")->play();
    }


    // target 2

    bool fxlight2 = false;
    bool fxdark2 = false;

    switch(e->key())
    {
        case Qt::Key_Z:
            newPos = player1->tryMoveTarget(1, 0, 1, gameMap);

            if(newPos != target2->getLocalPosition()) fxlight2 = true;
            else fxdark2 = true;

            target2->setLocalPosition(newPos);

        break;

        case Qt::Key_S:
            newPos = player1->tryMoveTarget(1, 0, -1, gameMap);

            if(newPos != target2->getLocalPosition()) fxlight2 = true;
            else fxdark2 = true;

            target2->setLocalPosition(newPos);
        break;

        case Qt::Key_Q:
            newPos = player1->tryMoveTarget(1, -1, 0, gameMap);

            if(newPos != target2->getLocalPosition()) fxlight2 = true;
            else fxdark2 = true;

            target2->setLocalPosition(newPos);
        break;

        case Qt::Key_D:
            newPos = player1->tryMoveTarget(1, 1, 0, gameMap);

            if(newPos != target2->getLocalPosition()) fxlight2 = true;
            else fxdark2 = true;

            target2->setLocalPosition(newPos);
        break;


        default:
        break;
    }

    if(fxlight2)
    {
        target2->addComponent(new EffectSpriteComponent(
                                       EffectSpriteComponent::TYPE_HIGHLIGHT, 60 * 0.15,
                                       ResourcesManager::getInstance()->getGameShader("texture"),
                                       ResourcesManager::getInstance()->getGameShader("texturelight")));

        ResourcesManager::getInstance()->getGameSound("swing")->play();
    }

    else if (fxdark2)
    {
        target2->addComponent(new EffectSpriteComponent(
                          EffectSpriteComponent::TYPE_HIGHLIGHT, 60 * 0.15,
                          ResourcesManager::getInstance()->getGameShader("texture"),
                          ResourcesManager::getInstance()->getGameShader("texturedark")));

        ResourcesManager::getInstance()->getGameSound("interface2")->play();
    }
}




void ImaginaWars::mouseReleaseEvent(QMouseEvent *e)
{/*
    //qDebug() << "CLICK " << e->x() << ";" << e->y();


    // il va falloir transformer tout ça dans le repère monde :o

    // merci http://antongerdelan.net/opengl/raycasting.html


    // 2d Viewport Coordinates -> 3d Normalised Device Coordinates

    float x = (2.0f * e->x()) / glWidth - 1.0f;
    float y = 1.0f - (2.0f * e->y()) / glHeight;
    float z = 1.0f;
    QVector3D ray_nds = QVector3D(x, y, z);

    // 4d Homogeneous Clip Coordinates

    QVector4D ray_clip = QVector4D(ray_nds.x(), ray_nds.y(), -1.0, 1.0);


   // 4d Eye (Camera) Coordinates

    QMatrix4x4 proj = GameScene::getInstance()->getProjection();

    QVector4D ray_eye = proj.inverted() * ray_clip;
    ray_eye = QVector4D(ray_eye.x(), ray_eye.y(), -1.0, 0.0);


    // 4d World Coordinates

    //QVector3D ray_wor = (inverse(view_matrix) * ray_eye).xyz;
    QVector4D q = QVector4D(GameScene::getInstance()->getLocalTransform() * ray_eye);
    QVector3D ray_wor = QVector3D(q.x(), q.y(), q.z());
    // don't forget to normalise the vector at some point
    ray_wor = ray_wor.normalized();


   qDebug() << "CLICK WORLD " << ray_wor.x() << ";" << ray_wor.y() << ";" << ray_wor.z();

   // x = +/- 0.55
   // y = +/- 0.33


    //QVector2D cas = gm->posToCase(QVector2D(ray_wor.x() * 20, ray_wor.y() * 20));

   int caseX = (ray_wor.x() + 0.55) / 1.10 * gameMap->getWidth();
   int caseY =(ray_wor.y() + 0.33) / 0.66 * gameMap->getHeight();
   if(caseX > gameMap->getWidth()) caseX = gameMap->getWidth();
   if(caseX < 0) caseX = 0;
   if(caseY > gameMap->getHeight()) caseY = gameMap->getHeight();
   if(caseY < 0) caseY = 0;

   QVector2D cas = QVector2D(caseX, caseY);


    qDebug() << "CLICKED CASE " << cas;

    //pathfinding->setTargetPos(cas);


    spr->getPathfinding()->setTargetPos(QVector2D(ray_wor.x() * 20, ray_wor.y() * 12));

    //gameMap->getSprite(cas)->addComponent(new EffectSpriteComponent(EffectSpriteComponent::TYPE_HIGHLIGHT, 60 * 1));
    gameMap->HighlightTile(cas.x(), cas.y());
*/
}



void ImaginaWars::win()
{
    qDebug() << "YOU WIN";

    Sprite *s = new Sprite("win", QVector3D(), 0, QVector2D(1, 0.18));
    s->createGeometry();
    GameScene::getInstance()->addChild(s);
}

void ImaginaWars::lose()
{
    qDebug() << "YOU LOSE";

    Sprite *s = new Sprite("lose", QVector3D(), 0, QVector2D(1, 0.18));
    s->createGeometry();
    GameScene::getInstance()->addChild(s);
}

