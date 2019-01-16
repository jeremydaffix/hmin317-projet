#ifndef SPRITE_H
#define SPRITE_H


#include <engine/model3d.h>


// Class représentant un Plan.
// Elle hérite de Model3D (objet 3D affichable), héritant elle-même de GameObject (classe générique,
// qui gère tout ce qui est conversion de repères, pose, graph de scène, etc).
class Sprite : public Model3D
{
public:

    // constructeur adapté d'un plan normal avec une texture
    Sprite(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1),
           QOpenGLShaderProgram* sh = NULL, QOpenGLTexture *tex = NULL);


    // constructeurs plus adaptés à une "vision 2D"

    Sprite(std::string name, QVector3D pos = QVector3D(), float rot = 0, QVector2D sc = QVector2D(1, 1),
           QOpenGLShaderProgram* sh = NULL);

    Sprite(QOpenGLTexture *tex, QVector3D pos = QVector3D(), float rot = 0, QVector2D sc = QVector2D(1, 1),
           QOpenGLShaderProgram* sh = NULL);


    // les 2 méthodes à redéfinir et spécifiques à la création / affichage des sommets du Plan !
    void createGeometry();
    void draw();

    //int getNbrVertices() const;
    //void setNbrVertices(int value);

protected:
    const int nbrVertices = 3;
    void init(QOpenGLTexture *tex, QVector3D pos, float rot, QVector2D sc, QOpenGLShaderProgram* sh);
};

#endif // SPRITE_H
