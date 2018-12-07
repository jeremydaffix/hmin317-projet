#include "model3d.h"



Model3D::Model3D(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh, QOpenGLTexture *tex) : GameObject (pos, rot, sc), indexBuf(QOpenGLBuffer::IndexBuffer)
{
    /*if(sh == NULL) shader = GameScene::getInstance()->getDefaultShader();
    else*/ shader = sh;
    texture = tex;

    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();
}

Model3D::~Model3D()
{
    arrayBuf.destroy();
    indexBuf.destroy();

    delete texture;
}

QOpenGLShaderProgram *Model3D::getShader() const
{
    return shader;
}

void Model3D::setShader(QOpenGLShaderProgram *value)
{
    shader = value;
}

QOpenGLTexture *Model3D::getTexture() const
{
    return texture;
}

void Model3D::setTexture(QOpenGLTexture *value)
{
    texture = value;
}


