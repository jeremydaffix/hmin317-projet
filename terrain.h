#ifndef TERRAIN_H
#define TERRAIN_H

#include <model3d.h>


// Class représentant un Terrain.
// Elle hérite de Model3D (objet 3D affichable), héritant elle-même de GameObject (classe générique,
// qui gère tout ce qui est conversion de repères, pose, graph de scène, etc).
// A noter qu'un Terrain est plus ou moins un plan dont certains sommets sont surrélevés, selon
// une heightmap chargée dans un fichier.
class Terrain : public Model3D
{
public:
    Terrain(QString path, int vert = 16, QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);
    ~Terrain();

    // les 2 méthodes à redéfinir et spécifiques à la création / affichage des sommets du Terrain !
    void createGeometry();
    void draw();

    int getNbrVertices() const;
    void setNbrVertices(int value);

protected:
    int nbrVertices;
    QImage *heightmap = NULL;

};

#endif // TERRAIN_H
