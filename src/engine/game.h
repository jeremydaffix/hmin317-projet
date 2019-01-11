#ifndef GAME_H
#define GAME_H

// classe abstraite dont doit hériter la classe principale du jeu


#include <engine/gamescene.h>
#include <engine/cube.h>
#include <engine/objet3d.h>
#include <engine/terrain.h>
#include <engine/plane.h>
#include <engine/sprite.h>
#include <engine/movingballcomponent.h>
#include <engine/spriteanimationcomponent.h>
#include <engine/resourcesmanager.h>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>

#include <math.h>



// direction pour le déplacement de la caméra
enum DIRECTION {
  NO,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  TURN_LEFT,
  TURN_RIGHT
};



class Game : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit Game(int _fps = 60, QWidget *parent = 0);
    virtual ~Game() override;

    int getFps() const;
    void setFps(int value);


    virtual void startGame();

    static Game *getInstance();

protected:

    static Game *instance; // pas vraiment un singleton puisque le constructeur est public et on doit créer un objet game explicitement dans l'app (main.cpp)

    int glWidth = 0, glHeight = 0;

    // événements entrée utilisateur
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;
    void timerEvent(QTimerEvent *e) override;

    // événements OpenGL
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // chargement ressources
    virtual void initShaders();
    virtual void initTextures();


private:

    QBasicTimer timer;

    int fps = 0;


//public slots:


};




#endif // GAME_H
