#ifndef PLANE_H
#define PLANE_H

#include <engine/model3d.h>


// Class représentant un Plan.
// Elle hérite de Model3D (objet 3D affichable), héritant elle-même de GameObject (classe générique,
// qui gère tout ce qui est conversion de repères, pose, graph de scène, etc).
class Plane : public Model3D
{
public:
    Plane(int vert = 16, QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL, QOpenGLTexture *tex = NULL);

    // les 2 méthodes à redéfinir et spécifiques à la création / affichage des sommets du Plan !
    void createGeometry();
    void draw();

    int getNbrVertices() const;
    void setNbrVertices(int value);

protected:
    int nbrVertices;
};

#endif // PLANE_H
