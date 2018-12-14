#ifndef OBJET3D_H
#define OBJET3D_H

#include <engine/model3d.h>

#include <string>
#include <QFile>
#include <QOpenGLBuffer>

using namespace std;

//la classe qui charge les objets 3d

typedef struct{
    QVector3D position;
    QVector3D normal;
}info_3d;

class Objet3d : public Model3D
{
public:



    Objet3d(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1), QOpenGLShaderProgram* sh = NULL);

    // les 2 méthodes à redéfinir et spécifiques à la création / affichage des sommets de l'objet !
    void createGeometry();
    void draw();
    bool loadobj(vector <QVector3D> & out_vertices, vector <QVector3D> & out_normals);
    const char* path;
    int taille;
    QOpenGLBuffer VBO;
};


#endif // OBJET3D_H
