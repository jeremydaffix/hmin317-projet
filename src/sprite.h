#ifndef SPRITE_H
#define SPRITE_H


#include <model3d.h>


// Class représentant un Plan.
// Elle hérite de Model3D (objet 3D affichable), héritant elle-même de GameObject (classe générique,
// qui gère tout ce qui est conversion de repères, pose, graph de scène, etc).
class Sprite : public Model3D
{
public:

    // constructeur adapté d'un plan normal avec une texture
    Sprite(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL, QOpenGLTexture *tex = NULL);

    // constructeur plus adapté à une "vision 2D"
    Sprite(QString path, QVector2D pos = QVector2D(), float rot = 0, QVector2D sc = QVector2D(1, 1), QOpenGLShaderProgram* sh = NULL);

    // les 2 méthodes à redéfinir et spécifiques à la création / affichage des sommets du Plan !
    void createGeometry();
    void draw();

    //int getNbrVertices() const;
    //void setNbrVertices(int value);

protected:
    const int nbrVertices = 3;
};

#endif // SPRITE_H
