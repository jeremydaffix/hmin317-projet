#ifndef ANIMATION2D_H
#define ANIMATION2D_H



#include <model3d.h>
#include <sprite.h>


// on met les différents sprites en children
// 1 branche par type d'animation
// OU PAS
// paramètre : fps

class Animation2D : public Model3D
{
public:

    /*Animation2D(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL, QOpenGLTexture *tex = NULL);

    void createGeometry();
    void draw();*/


protected:

    int fps = 1;
    Sprite *sprite;


};

#endif // ANIMATION2D_H
