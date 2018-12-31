#include "imaginawars.h"

ImaginaWars::ImaginaWars(int _fps) : Game(_fps)
{

}

void ImaginaWars::startGame()
{
    qDebug() << "IMAGINA WARS";

    GameMap *gm = new GameMap(":/resources/game/maps/test.json");
    gm->setLocalPosition(QVector3D(0.5,0.5,0));
    gm->setShader(ResourcesManager::getInstance()->getGameShader("texturedark"));
    gm->BuildMap();
    GameScene::getInstance()->addChild(gm);

    //gm->calcPath(QVector2D(1, 1), QVector2D(9, 9));


    Sprite *spr = new Sprite(NULL,
                             QVector2D(0, 0),
                             0,
                             QVector2D(0.08, 0.08),
                             ResourcesManager::getInstance()->getGameShader("texturetoon"));

    //spr->addComponent(new MovingBallComponent());
    spr->addComponent(new WalkPathfindingComponent(gm));

    //qDebug() << gm->CaseToPos(QVector2D(0,0));



    SpriteAnimationComponent *anim = new SpriteAnimationComponent(15);

    for(int i = 0 ; i < 12 ; ++i)
    {
        anim->addTexture(ResourcesManager::getInstance()->getGameTexture("knight_w_sw_" + std::to_string(i)));
    }

    spr->addComponent(anim);



    GameScene::getInstance()->addChild(spr);








    GameScene::getInstance()->createGeometry();
    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
    GameScene::getInstance()->setLocalPosition(QVector3D(0,0,15));


}



void ImaginaWars::initShaders()
{
    QOpenGLShaderProgram * shaderTexture = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader.glsl");
    ResourcesManager::getInstance()->addGameShader("texture", shaderTexture);

    QOpenGLShaderProgram * shaderTextureToon = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_toon.glsl");
    ResourcesManager::getInstance()->addGameShader("texturetoon", shaderTextureToon);

    QOpenGLShaderProgram * shaderTextureDark = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_dark.glsl");
    ResourcesManager::getInstance()->addGameShader("texturedark", shaderTextureDark);

    GameScene::getInstance()->setDefaultShader(shaderTexture);
    //GameScene::getInstance()->setDefaultShader(shaderTextureToon);
}

void ImaginaWars::initTextures()
{
    QOpenGLTexture *textureDice = ResourcesManager::getInstance()->loadTexture(":/Resources/Textures/cube.png");
    ResourcesManager::getInstance()->addGameTexture("cube", textureDice);


    // textures knight

    string name = "knight";

    for(int i = 0 ; i < 12 ; ++i)
    {
        //std::string nameInGame = name + "_w_s_" + std::to_string(i);
        QString qs = ((i < 10 ? "0" : "") + std::to_string(i)).c_str();



        ResourcesManager::getInstance()->addGameTexture(name + "_w_n_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking n00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_ne_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking ne00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_e_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking e00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_se_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking se00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_s_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_sw_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking sw00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_w_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking w00" + qs + ".png"));

        ResourcesManager::getInstance()->addGameTexture(name + "_w_nw_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking nw00" + qs + ".png"));
    }



    // tiles

    int nbrTiles = 66;
    for(int i = 1 ; i <= nbrTiles ; ++i)
    {
        QString qs = ((i < 10 ? "0" : "") + std::to_string(i)).c_str();

        ResourcesManager::getInstance()->addGameTexture("medieval_tile_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/medievalrtspack/Tile/medievalTile_" + qs + ".png"));
    }


    GameScene::getInstance()->setDefaultTexture(textureDice);
}
