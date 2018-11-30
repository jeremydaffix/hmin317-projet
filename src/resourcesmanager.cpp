#include "resourcesmanager.h"

ResourcesManager* ResourcesManager::instance = NULL;

ResourcesManager *ResourcesManager::getInstance() {

    if(instance == NULL) instance = new ResourcesManager();

    return instance;
}


ResourcesManager::ResourcesManager()
{

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
