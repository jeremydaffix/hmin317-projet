#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <unordered_map>
#include <iostream>


class ResourcesManager : public QObject
{
public:

    static ResourcesManager* getInstance();


    virtual ~ResourcesManager();


    void addGameShader(std::string name, QOpenGLShaderProgram* sh);
    void addGameTexture(std::string name, QOpenGLTexture* tex);
    //void addGameFont(std::string name, FT_Face* font);

    QOpenGLShaderProgram* getGameShader(std::string name);
    QOpenGLTexture* getGameTexture(std::string name);
    //FT_Face * getGameFont(std::string name);


    // raccourci pour charger un shader
    void loadShader(QOpenGLShaderProgram &shader, QString vpath, QString fpath);
    QOpenGLShaderProgram *loadShader(QString vpath, QString fpath);

    // raccourci pour charger une texture
    QOpenGLTexture *loadTexture(QString path);

    // raccourci pour charger une police
    //FT_Face *loadFont(std::string path);


    // transformer un texte en texture
    //QOpenGLTexture *createTextureFromText(std::string txt, int size, FT_Face *font);

protected:
    static ResourcesManager *instance;


    // listes de tous les shaders et textures du jeu
    // pour ne pas avoir à les charger plusieurs fois
    // et pour les libérer ensuite facilement
    std::unordered_map<std::string, QOpenGLShaderProgram*> gameShaders;
    std::unordered_map<std::string, QOpenGLTexture*> gameTextures;
    //std::unordered_map<std::string, FT_Face*> gameFonts;

    //FT_Library ft;

private:
    ResourcesManager();
};

#endif // RESOURCESMANAGER_H
