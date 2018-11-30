#include "gamescene.h"


//GameScene *GameScene::instance = nullptr;
int GameScene::currentNumInstance = 0;
GameScene * GameScene::instances[];

GameScene *GameScene::getInstance()
{

    if(!
            instances[currentNumInstance]) {
            instances[currentNumInstance] = new GameScene();
        }

        return instances[currentNumInstance];
}

GameScene::GameScene()
{

}

int GameScene::getCurrentNumInstance()
{
    return currentNumInstance;
}

void GameScene::setCurrentNumInstance(int value)
{
    currentNumInstance = value;
}

QMatrix4x4 GameScene::getProjection() const
{
    return projection;
}

void GameScene::setProjection(const QMatrix4x4 &value)
{
    projection = value;
}


// on ne bouge pas la caméra mais la scène qui est la racine du graphe de scène
// redéfinition de getLocalTransform() pour "inverser" la transformation,
// afin de simuler le fait de bouger non pas la scène mais une caméra
QMatrix4x4 GameScene::getLocalTransform() const
{
    QMatrix4x4 transf;

    transf.rotate(getLocalRotation().inverted());
    transf.translate(- getLocalPosition());
    transf.scale(getLocalScale());

    return transf;
}



QOpenGLShaderProgram *GameScene::getDefaultShader()
{
    return defaultShader;
}

void GameScene::setDefaultShader(QOpenGLShaderProgram *value)
{
    defaultShader = value;
}
