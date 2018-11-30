#include "model3d.h"



Model3D::Model3D(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh) : GameObject (pos, rot, sc), indexBuf(QOpenGLBuffer::IndexBuffer)
{
    /*if(sh == NULL) shader = GameScene::getInstance()->getDefaultShader();
    else*/ shader = sh;

    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();
}

Model3D::~Model3D()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

QOpenGLShaderProgram *Model3D::getShader() const
{
    return shader;
}

void Model3D::setShader(QOpenGLShaderProgram *value)
{
    shader = value;
}


