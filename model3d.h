#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include <gamescene.h>
//#include <gameobject.h>

//class GameScene;


// Classe représentant un objet 3D affichable.
// Elle hérite de GameObject, qui lui fournit tout ce qu'il faut pour la gestion du
// graph de scène, des calculs de position / rotation / scale / repère, etc.
// On ne créée pas directement d'instance de cette classe, mais les classes objets 3D
// "concrets" en hérite (Cube, Plan, Terrain, Sprite,...).
class Model3D : public GameObject, protected QOpenGLFunctions
{
public:

    Model3D(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);
    virtual ~Model3D();

    //virtual void CreateGeometry();
    //virtual void Draw();

    QOpenGLShaderProgram *getShader() const;
    void setShader(QOpenGLShaderProgram *value);

protected:

    // buffers OpenGL
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    // shader de l'objet 3D
    QOpenGLShaderProgram *shader = NULL;

};

#endif // DISPLAYABLEOBJECT_H
