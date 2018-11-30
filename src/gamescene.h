#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QOpenGLTexture>
#include <gameobject.h>


// Classe représentant la Scène / Caméra.
// Il s'agit d'un GameObject comme un autre, qui est la racine du graph de scène.
// Comme il n'y a qu'une seule scène dans notre jeu (sauf pour le TP3 qui a 4 fenêtres), nous avons utilisé un
// Pattern Singleton pour accéder proprement à l'unique instance de la scène.
class GameScene : public GameObject
{
public:
    static GameScene* getInstance();

    // on peut définir un shader par défaut pour les objets de la scène
    QOpenGLShaderProgram *getDefaultShader();
    void setDefaultShader(QOpenGLShaderProgram *value);

    // on redéfinit ces 2 méthodes, pour simuler l'utilisation d'une caméra
    // en effet, en OpenGL, c'est la scène qui bouge, et non la caméra,
    // mais il est plus intuitif de faire "comme si" on bougeait une caméra
    // -> on inverse juste la translation et la rotation par rapport au getProjection() du GameObject "normal"
    QMatrix4x4 getProjection() const;
    void setProjection(const QMatrix4x4 &value);

    QMatrix4x4 getLocalTransform() const;

    // POUR LE TP3 ON EST OBLIGES D'AVOIR 4 INSTANCES INDEPENDANTES DANS UN TABLEAU
    // astuce : on utilise un indice static currentNumInstance, ce qui rend l'utilisation transparente
    static int getCurrentNumInstance();
    static void setCurrentNumInstance(int value);

    QOpenGLTexture *getDefaultTexture() const;
    void setDefaultTexture(QOpenGLTexture *value);

private:
    GameScene(); // SINGLETON


protected:

    QOpenGLShaderProgram* defaultShader;
    QOpenGLTexture *defaultTexture;
    //static GameScene* instance;

    static GameScene *instances[4]; // POUR LE TP3 ON EST OBLIGES D'AVOIR 4 INSTANCES INDEPENDANTES DANS UN TABLEAU
    static int currentNumInstance;

    QMatrix4x4 projection;

};

#endif // GAMESCENE_H
