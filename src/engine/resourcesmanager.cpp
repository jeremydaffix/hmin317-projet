#include "engine/resourcesmanager.h"

ResourcesManager* ResourcesManager::instance = NULL;

ResourcesManager *ResourcesManager::getInstance() {

    if(instance == NULL) instance = new ResourcesManager();

    return instance;
}

ResourcesManager::~ResourcesManager()
{
    // libérer en un seul lieu :
    //  images
    //  sons
    //  shaders
    // fonts

    // les objets du moteur (gameobject, components,...) sont libérés par le destructeur de la scène (puis de chaque objet de la hiérarchie)



    for( const auto& s : gameShaders )
    {
        std::cout << "freeing shader " << s.first << std::endl;

        delete s.second;
    }


    for( const auto& t : gameTextures )
    {
        //std::cout << "freeing texture " << t.first << std::endl;

        delete t.second;
    }


    /*for( const auto& t : gameFonts )
    {
        //std::cout << "freeing font " << t.first << std::endl;

        delete t.second;
    }*/

    for( const auto& t : gameSounds )
    {
        //std::cout << "freeing sound " << t.first << std::endl;

        delete t.second;
    }
}

void ResourcesManager::addGameShader(std::string name, QOpenGLShaderProgram *sh)
{
    gameShaders[name] = sh;
}

void ResourcesManager::addGameTexture(std::string name, QOpenGLTexture *tex)
{
    gameTextures[name] = tex;
}

void ResourcesManager::addGameSound(std::string name, QSoundEffect *e)
{
    gameSounds[name] = e;
}

/*void ResourcesManager::addGameFont(std::string name, FT_Face *font)
{
    gameFonts[name] = font;
}*/

QOpenGLShaderProgram *ResourcesManager::getGameShader(std::string name)
{
    return gameShaders[name];
}

QOpenGLTexture *ResourcesManager::getGameTexture(std::string name)
{
    return gameTextures[name];
}

QSoundEffect *ResourcesManager::getGameSound(std::string name)
{
    return gameSounds[name];
}

/*FT_Face *ResourcesManager::getGameFont(std::string name)
{
    return gameFonts[name];
}*/


ResourcesManager::ResourcesManager()
{
    /*if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;*/
}


// méthode pour simplifier le chargement d'un shader

 void ResourcesManager::loadShader(QOpenGLShaderProgram &shader, QString vpath, QString fpath)
 {
     // Compile vertex shader
     if (!shader.addShaderFromSourceFile(QOpenGLShader::Vertex, vpath))
         return;//close();

     // Compile fragment shader
     if (!shader.addShaderFromSourceFile(QOpenGLShader::Fragment, fpath))
         return;//close();
 }

QOpenGLShaderProgram *ResourcesManager::loadShader(QString vpath, QString fpath)
{
    QOpenGLShaderProgram *shader = new QOpenGLShaderProgram();

    // Compile vertex shader
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vpath))
        return NULL;//close();

    // Compile fragment shader
    if (!shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fpath))
        return NULL;//close();

    return shader;
}




 QOpenGLTexture *ResourcesManager::loadTexture(QString path)
 {

     QOpenGLTexture *texture = new QOpenGLTexture(QImage(path).mirrored());

     // Set nearest filtering mode for texture minification
     texture->setMinificationFilter(QOpenGLTexture::Nearest);
     // Set bilinear filtering mode for texture magnification
     texture->setMagnificationFilter(QOpenGLTexture::Linear);
     // Wrap texture coordinates by repeating
     // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
     texture->setWrapMode(QOpenGLTexture::Repeat);


     return texture;
 }

 QSoundEffect *ResourcesManager::loadSound(std::string path, float v)
 {
     // bien MAIS avec une seule instance on ne peut jouer le son qu'une seule fois en même temps !
     // si besoin de jouer le même son plusieurs fois en même temps
     // -> directement utiliser des QSoundEffect dans le jeu

     QSoundEffect *effect = new QSoundEffect();
     effect->setSource(QUrl(QString(path.c_str())));
     effect->setLoopCount(1);
     effect->setVolume(v);
     //effect->play();

     return effect;
 }

 void ResourcesManager::playBackgroundMusic(std::string path, int v)
 {
     qmp.stop();
     qmpl.clear();

     qmp.setVolume(v);

     qmpl.addMedia(QUrl(QString(path.c_str())));
     //qmpl.setCurrentIndex(0);
     qmpl.setPlaybackMode(QMediaPlaylist::Loop);

     qmp.setPlaylist(&qmpl);
     qmp.play(); // loop ?
 }

 /*void ResourcesManager::playSoundEffect(std::string path, float v, int loop)
 {
     QSoundEffect effect;
     effect.setSource(QUrl(QString(path.c_str())));
     effect.setLoopCount(loop);
     effect.setVolume(v);
     effect.play();
 }*/

 /*FT_Face *ResourcesManager::loadFont(std::string path)
 {
     FT_Face *face = new FT_Face();

     if (FT_New_Face(ft, path.c_str(), gameFonts.size(), face))
         std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

     return face;
 }*/

 /*QOpenGLTexture *ResourcesManager::createTextureFromText(std::string txt, int size, FT_Face *font)
 {
     // 1 sprite par caractère :'(
 }*/
