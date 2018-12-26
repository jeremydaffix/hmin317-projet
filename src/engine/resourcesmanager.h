#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

#include <unordered_map>
#include <iostream>


class ResourcesManager : public QObject
{
public:

    static ResourcesManager* getInstance();


    virtual ~ResourcesManager();

    // listes de tous les shaders et textures du jeu
    // pour ne pas avoir à les charger plusieurs fois
    // et pour les libérer ensuite facilement
    std::unordered_map<std::string, QOpenGLShaderProgram*> gameShaders;
    std::unordered_map<std::string, QOpenGLTexture*> gameTextures;


    void addGameShader(std::string name, QOpenGLShaderProgram* sh);
    void addGameTexture(std::string name, QOpenGLTexture* tex);

    QOpenGLShaderProgram* getGameShader(std::string name);
    QOpenGLTexture* getGameTexture(std::string name);


    // raccourci pour charger un shader
    void loadShader(QOpenGLShaderProgram &shader, QString vpath, QString fpath);
    QOpenGLShaderProgram *loadShader(QString vpath, QString fpath);

    // raccourci pour charger une texture
    QOpenGLTexture *loadTexture(QString path);

protected:
    static ResourcesManager *instance;

private:
    ResourcesManager();
};

#endif // RESOURCESMANAGER_H
