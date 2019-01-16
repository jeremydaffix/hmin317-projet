#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimedia/QSoundEffect>


//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <unordered_map>
#include <iostream>


// cette classe s'occupe de gérer les ressources
// de différents types (sprites, sons,...)

class ResourcesManager : public QObject
{
public:

    static ResourcesManager* getInstance();


    virtual ~ResourcesManager();


    // ajouter une ressource au dictionnaire de ressources, sous un nom
    void addGameShader(std::string name, QOpenGLShaderProgram* sh);
    void addGameTexture(std::string name, QOpenGLTexture* tex);
    //void addGameFont(std::string name, FT_Face* font);
    void addGameSound(std::string name, QSoundEffect * e);

    // récupérer une ressource dans le dictionnaire de ressources, à partir de son nom
    QOpenGLShaderProgram* getGameShader(std::string name);
    QOpenGLTexture* getGameTexture(std::string name);
    //FT_Face * getGameFont(std::string name);
    QSoundEffect *getGameSound(std::string name);


    // raccourci pour charger un shader
    void loadShader(QOpenGLShaderProgram &shader, QString vpath, QString fpath);
    QOpenGLShaderProgram *loadShader(QString vpath, QString fpath);

    // raccourci pour charger une texture
    QOpenGLTexture *loadTexture(QString path);

    // raccourci pour charger une police
    //FT_Face *loadFont(std::string path);

    // raccourci pour charger un son
    QSoundEffect *loadSound(std::string path, float v = 0.65);


    // transformer un texte en texture
    //QOpenGLTexture *createTextureFromText(std::string txt, int size, FT_Face *font);


    void playBackgroundMusic(std::string path, int v = 40);
    //void playSoundEffect(std::string path, float v = 0.75, int loop = 1);

protected:
    static ResourcesManager *instance;


    // listes de tous les shaders et textures du jeu
    // pour ne pas avoir à les charger plusieurs fois
    // et pour les libérer ensuite facilement
    std::unordered_map<std::string, QOpenGLShaderProgram*> gameShaders;
    std::unordered_map<std::string, QOpenGLTexture*> gameTextures;
    //std::unordered_map<std::string, FT_Face*> gameFonts;
    std::unordered_map<std::string, QSoundEffect*> gameSounds;

    QMediaPlayer qmp;
    QMediaPlaylist qmpl;

    //FT_Library ft;

private:
    ResourcesManager();
};

#endif // RESOURCESMANAGER_H
