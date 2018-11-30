#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

class ResourcesManager : public QObject
{
public:

    static ResourcesManager* getInstance();

    // raccourci pour charger un shader
    void loadShader(QOpenGLShaderProgram &shader, QString vpath, QString fpath);

    // raccourci pour charger une texture
    QOpenGLTexture *loadTexture(QString path);

protected:
    static ResourcesManager *instance;

private:
    ResourcesManager();
};

#endif // RESOURCESMANAGER_H
