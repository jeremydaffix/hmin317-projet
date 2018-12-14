#include "game.h"



Game::Game(int _fps, QWidget *parent) :
    QOpenGLWidget(parent)
{

    fps = _fps;
}

Game::~Game()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();

    delete textureDice;

    GameScene::getInstance()->destroy(); // destruction de toute la hiérarchie et des components
    delete GameScene::getInstance();

    doneCurrent();
}

//! [0]
void Game::mousePressEvent(QMouseEvent *e)
{

}

void Game::mouseReleaseEvent(QMouseEvent *e)
{

}
//! [0]

//! [1]
void Game::timerEvent(QTimerEvent *)
{
    GameScene::getInstance()->fixedUpdate();


    update();


    // déplacement géré ici
    // position pas changée dans l'event clavier
    // on estime que timerEvent est lancée à un fps fixe

    bool needUpdate = true;

    QVector3D rotCam = GameScene::getInstance()->getLocalRotation().toEulerAngles();

    switch(movementDirection)
    {
        case DIRECTION::UP:
            GameScene::getInstance()->move(QVector3D(0, 0, -0.2));
        break;

        case DIRECTION::DOWN:
            GameScene::getInstance()->move(QVector3D(0, 0, 0.2));
        break;

        case DIRECTION::LEFT:
            GameScene::getInstance()->move(QVector3D(-0.2, 0, 0));
        break;

        case DIRECTION::RIGHT:
            GameScene::getInstance()->move(QVector3D(0.2, 0, 0));
        break;

        case DIRECTION::TURN_LEFT:
            rotCam.setY(rotCam.y() + 3);
        break;

        case DIRECTION::TURN_RIGHT:
            rotCam.setY(rotCam.y() - 3);
        break;

        default:
            needUpdate = false;
        break;

    }

    QVector3D posCam = GameScene::getInstance()->getLocalPosition();
    if(posCam.x() < -12) posCam.setX(-12);
    if(posCam.x() > 12) posCam.setX(12);
    if(posCam.z() < -12) posCam.setZ(-12);
    if(posCam.z() > 12) posCam.setZ(12);
    GameScene::getInstance()->setLocalPosition(posCam);

    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(rotCam));

    if(needUpdate) update();
}
//! [1]



void Game::keyPressEvent(QKeyEvent* e)
{
    switch(e->key())
    {
        case Qt::Key_Z:
            movementDirection = DIRECTION::UP;
        break;

        case Qt::Key_S:
            movementDirection = DIRECTION::DOWN;
        break;

        case Qt::Key_Q:
            movementDirection = DIRECTION::LEFT;
        break;

        case Qt::Key_D:
            movementDirection = DIRECTION::RIGHT;
        break;

        case Qt::Key_A:
            movementDirection = DIRECTION::TURN_LEFT;
        break;

        case Qt::Key_E:
            movementDirection = DIRECTION::TURN_RIGHT;
        break;

        default:
            movementDirection = DIRECTION::NO;
        break;
    }


}

void Game::keyReleaseEvent(QKeyEvent* e)
{
    movementDirection = DIRECTION::NO;
}



void Game::initializeGL()
{

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    //geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(1000 / fps, this);




    // CREATION DU GRAPHE DE SCENE ET DES OBJETS 3D
/*
    Cube *cube = new Cube(QVector3D(-0.5, 5, -5.), QQuaternion::fromEulerAngles(0, 20, 0), QVector3D(1.5, 2.0, 1.0), NULL, textureDice2);
    Cube *cube2 = new Cube(QVector3D(0.5, 5, -5));
    Cube *cube3 = new Cube(QVector3D(2, 2, 0), QQuaternion(), QVector3D(1, 1, 1));
   // Objet3d *test = new Objet3d(QVector3D(2, 2, 0), QQuaternion(), QVector3D(1, 1, 1));
   // test->path = ":/pillow_low.obj";
   // test->setShader(&shaderTest);


    GameScene::getInstance()->addChild(cube);
    //GameScene::getInstance()->addChild(test);
    GameScene::getInstance()->addChild(cube2);
    cube2->addChild(cube3);

    cube2->addComponent(new MovingCubeComponent());*/

    /*terrain = new Terrain(":/island_heightmap.png",
                          128, QVector3D(0, -3, 0), QQuaternion::fromEulerAngles(-90, 0, 0), QVector3D(2, 2, 2));
    terrain->setShader(&shaderTerrain);
    GameScene::getInstance()->addChild(terrain);*/


    //Sprite *spr = new Sprite(QVector3D(0, -3, 0), QQuaternion::fromEulerAngles(0, 0, 0), QVector3D(1, 1, 1));
    //Sprite *spr = new Sprite(":/resources/textures/cube2.png", QVector2D(2, 2), 45, QVector2D(1, 1));

    Sprite *spr = new Sprite(ResourcesManager::getInstance()->loadTexture(":/resources/textures/testalpha.png"), QVector2D(0, 0), 10, QVector2D(0.1, 0.1));
    spr->addComponent(new MovingBallComponent());

    SpriteAnimationComponent *anim = new SpriteAnimationComponent(20);

    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0000.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0001.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0002.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0003.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0004.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0005.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0006.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0007.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0008.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0009.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0010.png"));
    anim->addTexture(ResourcesManager::getInstance()->loadTexture(":/resources/textures/units/knight/city/walking s0011.png"));

    spr->addComponent(anim);

    GameScene::getInstance()->addChild(spr);




    GameScene::getInstance()->createGeometry();
    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
    GameScene::getInstance()->setLocalPosition(QVector3D(0,0,50));

}





// chargement de tous les shaders
void Game::initShaders()
{

    ResourcesManager::getInstance()->loadShader(shaderTexture, ":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader.glsl");
    ResourcesManager::getInstance()->loadShader(shaderTest, ":/resources/shaders/vshader.glsl", ":/resources/shaders/shader_Objet.glsl");
    ResourcesManager::getInstance()->loadShader(shaderTerrain, ":/resources/shaders/vshader_color.glsl", ":/resources/shaders/fshader_color.glsl");

    ResourcesManager::getInstance()->loadShader(shaderTerrainWinter, ":/resources/shaders/vshader_winter.glsl", ":/resources/shaders/fshader_color.glsl");
    ResourcesManager::getInstance()->loadShader(shaderTerrainSpring, ":/resources/shaders/vshader_spring.glsl", ":/resources/shaders/fshader_color.glsl");
    ResourcesManager::getInstance()->loadShader(shaderTerrainSummer, ":/resources/shaders/vshader_summer.glsl", ":/resources/shaders/fshader_color.glsl");
    ResourcesManager::getInstance()->loadShader(shaderTerrainAutumn, ":/resources/shaders/vshader_autumn.glsl", ":/resources/shaders/fshader_color.glsl");


    GameScene::getInstance()->setDefaultShader(&shaderTexture);

}
//! [3]



// chargement des textures utilisées
void Game::initTextures()
{

    textureDice = ResourcesManager::getInstance()->loadTexture(":/Resources/Textures/cube.png");
    textureDice2 = ResourcesManager::getInstance()->loadTexture(":/Resources/Textures/cube2.png");

    GameScene::getInstance()->setDefaultTexture(textureDice);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

int Game::getFps() const
{
    return fps;
}

void Game::setFps(int value)
{
    fps = value;
}
//! [4]

//! [5]
void Game::resizeGL(int w, int h)
{

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;


    // Reset projection
    QMatrix4x4 proj;
    proj.setToIdentity();

    // Set perspective projection
    proj.perspective(fov, aspect, zNear, zFar);

    GameScene::getInstance()->setProjection(proj);
}
//! [5]

void Game::paintGL()
{

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // à chaque rafraîchissement :
    // on parse l'arbre du graphe de scène pour appeler les draw() de tous les objets (GameObject) à afficher

    GameScene::getInstance()->update(); // pour les components
    GameScene::getInstance()->draw();
}



