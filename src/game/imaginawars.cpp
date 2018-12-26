#include "imaginawars.h"

ImaginaWars::ImaginaWars(int _fps) : Game(_fps)
{

}

void ImaginaWars::startGame()
{
    qDebug() << "IMAGINA WARS";



    Sprite *spr = new Sprite(NULL,
                             QVector2D(0, 0),
                             10,
                             QVector2D(0.1, 0.1));

    spr->addComponent(new MovingBallComponent());

    SpriteAnimationComponent *anim = new SpriteAnimationComponent(20);

    for(int i = 0 ; i < 12 ; ++i)
    {
        anim->addTexture(ResourcesManager::getInstance()->getGameTexture("knight_w_s_" + std::to_string(i)));
    }

    spr->addComponent(anim);

    GameScene::getInstance()->addChild(spr);




    GameScene::getInstance()->createGeometry();
    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
    GameScene::getInstance()->setLocalPosition(QVector3D(0,0,10));
}



void ImaginaWars::initShaders()
{
    QOpenGLShaderProgram * shaderTexture = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader.glsl");
    ResourcesManager::getInstance()->addGameShader("texture", shaderTexture);

    GameScene::getInstance()->setDefaultShader(shaderTexture);
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


    GameScene::getInstance()->setDefaultTexture(textureDice);
}
