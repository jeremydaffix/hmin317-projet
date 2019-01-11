#include "engine/game.h"



Game* Game::instance = NULL;


Game::Game(int _fps, QWidget *parent) :
    QOpenGLWidget(parent)
{

    fps = _fps;

    instance = this;
}

Game::~Game()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();

    GameScene::getInstance()->destroy(); // destruction de toute la hiérarchie et des components
    delete GameScene::getInstance();

    delete ResourcesManager::getInstance(); // destruction des ressources

    doneCurrent();
}




void Game::mousePressEvent(QMouseEvent *e)
{
}

void Game::mouseReleaseEvent(QMouseEvent *e)
{
}


void Game::keyPressEvent(QKeyEvent* e)
{
}

void Game::keyReleaseEvent(QKeyEvent* e)
{
}



void Game::timerEvent(QTimerEvent *)
{
    GameScene::getInstance()->fixedUpdate();

    update();
}



void Game::initializeGL()
{

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();

    initTextures();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE) ;
    glEnable(GL_BLEND);

    // Enable depth buffer
    //glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);


    // Use QBasicTimer because its faster than QTimer
    timer.start(1000 / fps, this);



    startGame();

}





// chargement de tous les shaders
void Game::initShaders()
{
    //GameScene::getInstance()->setDefaultShader(&shaderTexture);
}



// chargement des textures utilisées
void Game::initTextures()
{
    //GameScene::getInstance()->setDefaultTexture(textureDice);
}


int Game::getFps() const
{
    return fps;
}

void Game::setFps(int value)
{
    fps = value;
}


void Game::startGame()
{
    qDebug() << "Override startGame() for your own game!";
}

Game *Game::getInstance()
{
    return instance;
}


void Game::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0; // eventuellement pouvoir passer au constructeur


    // Reset projection
    QMatrix4x4 proj;
    proj.setToIdentity();

    // Set perspective projection
    proj.perspective(fov, aspect, zNear, zFar);

    GameScene::getInstance()->setProjection(proj);

    glWidth = w;
    glHeight = h;
}



void Game::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // à chaque rafraîchissement :
    // on parse l'arbre du graphe de scène pour appeler les draw() de tous les objets (GameObject) à afficher

    GameScene::getInstance()->update(); // pour les components
    GameScene::getInstance()->draw();
}



