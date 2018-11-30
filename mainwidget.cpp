/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"


#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(int _fps, int _idScene, QWidget *parent) :
    QOpenGLWidget(parent),
    //geometries(0),
    texture(0),
    angularSpeed(0)
{

    fps = _fps;
    idScene = _idScene;

}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    //delete heightmap;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{

}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{

}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    GameScene::setCurrentNumInstance(idScene);

    GameScene::getInstance()->fixedUpdate();


    update();


    // déplacement géré ici
    // position pas changée dans l'event clavier
    // on estime que timerEvent est lancée à un fps fixe

    bool needUpdate = true;

    QVector3D rotCam = GameScene::getInstance()->getLocalRotation().toEulerAngles();

    switch(movementDirection)
    {
        case DIRECTION::UP:
            GameScene::getInstance()->move(QVector3D(0, 0, -0.2));
        break;

        case DIRECTION::DOWN:
            GameScene::getInstance()->move(QVector3D(0, 0, 0.2));
        break;

        case DIRECTION::LEFT:
            GameScene::getInstance()->move(QVector3D(-0.2, 0, 0));
        break;

        case DIRECTION::RIGHT:
            GameScene::getInstance()->move(QVector3D(0.2, 0, 0));
        break;

        case DIRECTION::TURN_LEFT:
            rotCam.setY(rotCam.y() + 3);
        break;

        case DIRECTION::TURN_RIGHT:
            rotCam.setY(rotCam.y() - 3);
        break;

        default:
            needUpdate = false;
        break;

    }

    QVector3D posCam = GameScene::getInstance()->getLocalPosition();
    if(posCam.x() < -12) posCam.setX(-12);
    if(posCam.x() > 12) posCam.setX(12);
    if(posCam.z() < -12) posCam.setZ(-12);
    if(posCam.z() > 12) posCam.setZ(12);
    GameScene::getInstance()->setLocalPosition(posCam);

    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(rotCam));

    if(needUpdate) update();
}
//! [1]



void MainWidget::keyPressEvent(QKeyEvent* e)
{

    GameScene::setCurrentNumInstance(idScene);

    switch(e->key())
    {
        case Qt::Key_Z:
            movementDirection = DIRECTION::UP;
        break;

        case Qt::Key_S:
            movementDirection = DIRECTION::DOWN;
        break;

        case Qt::Key_Q:
            movementDirection = DIRECTION::LEFT;
        break;

        case Qt::Key_D:
            movementDirection = DIRECTION::RIGHT;
        break;

        case Qt::Key_A:
            movementDirection = DIRECTION::TURN_LEFT;
        break;

        case Qt::Key_E:
            movementDirection = DIRECTION::TURN_RIGHT;
        break;

        default:
            movementDirection = DIRECTION::NO;
        break;
    }


    /*switch(e->key())
    {
        case Qt::Key_Up:
            if(rotationSpeed < 10.0) rotationSpeed += 0.1;
        break;

        case Qt::Key_Down:
            if(rotationSpeed > 0.2) rotationSpeed -= 0.1;
        break;

        default:
        break;
    }*/

}

void MainWidget::keyReleaseEvent(QKeyEvent* e)
{
    movementDirection = DIRECTION::NO;
}



void MainWidget::initializeGL()
{
    GameScene::setCurrentNumInstance(idScene);


    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    //geometries = new GeometryEngine;

    // Use QBasicTimer because its faster than QTimer
    timer.start(1000 / fps, this);




    // CREATION DU GRAPHE DE SCENE ET DES OBJETS 3D

    Cube *cube = new Cube(QVector3D(-0.5, 5, -5.), QQuaternion::fromEulerAngles(0, 20, 0), QVector3D(1.5, 2.0, 1.0));
    Cube *cube2 = new Cube(QVector3D(0.5, 5, -5));
    Cube *cube3 = new Cube(QVector3D(2, 2, 0), QQuaternion(), QVector3D(1, 1, 1));
   // Objet3d *test = new Objet3d(QVector3D(2, 2, 0), QQuaternion(), QVector3D(1, 1, 1));
   // test->path = ":/pillow_low.obj";
   // test->setShader(&shaderTest);


    GameScene::getInstance()->addChild(cube);
    //GameScene::getInstance()->addChild(test);
    GameScene::getInstance()->addChild(cube2);
    cube2->addChild(cube3);

    cube2->addComponent(new MovingCubeComponent());

    terrain = new Terrain(":/island_heightmap.png",
                          128, QVector3D(0, -3, 0), QQuaternion::fromEulerAngles(-90, 0, 0), QVector3D(2, 2, 2));
    terrain->setShader(&shaderTerrain);
    GameScene::getInstance()->addChild(terrain);

    GameScene::getInstance()->createGeometry();

    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
}


// méthode pour simplifier le chargement d'un shader
 void MainWidget::loadShader(QOpenGLShaderProgram &shader, QString vpath, QString fpath)
 {
     // Compile vertex shader
     if (!shader.addShaderFromSourceFile(QOpenGLShader::Vertex, vpath))
         close();

     // Compile fragment shader
     if (!shader.addShaderFromSourceFile(QOpenGLShader::Fragment, fpath))
         close();
 }


// chargement de tous les shaders
void MainWidget::initShaders()
{
    GameScene::setCurrentNumInstance(idScene);


    loadShader(shaderDice, ":/vshader.glsl", ":/fshader.glsl");
    loadShader(shaderTest, ":/vshader.glsl", ":/fshader_Objet.glsl");
    loadShader(shaderTerrain, ":/vshader_color.glsl", ":/fshader_color.glsl");

    loadShader(shaderTerrainWinter, ":/vshader_winter.glsl", ":/fshader_color.glsl");
    loadShader(shaderTerrainSpring, ":/vshader_spring.glsl", ":/fshader_color.glsl");
    loadShader(shaderTerrainSummer, ":/vshader_summer.glsl", ":/fshader_color.glsl");
    loadShader(shaderTerrainAutumn, ":/vshader_autumn.glsl", ":/fshader_color.glsl");


    GameScene::getInstance()->setDefaultShader(&shaderDice);

}
//! [3]

// chargement des textures utilisées
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    //heightmap = new QImage(QImage(":/island_heightmap.png"));

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    GameScene::setCurrentNumInstance(idScene);


    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    ////const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;
    const qreal zNear = 1.0, zFar = 100.0, fov = 45.0;


    // Reset projection
    QMatrix4x4 proj;
    proj.setToIdentity();

    // Set perspective projection
    proj.perspective(fov, aspect, zNear, zFar);

    GameScene::getInstance()->setProjection(proj);
}
//! [5]

void MainWidget::paintGL()
{
    GameScene::setCurrentNumInstance(idScene);


    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();


    // à chaque rafraîchissement :
    // on parse l'arbre du graphe de scène pour appeler les draw() de tous les objets (GameObject) à afficher

    GameScene::getInstance()->update(); // pour les components, EN COURS DE DEV
    GameScene::getInstance()->draw();
}





void MainWidget::setSeason(int season)
{
    qDebug() << "Scene " << idScene << " : SEASON " << season;

    if(season == 0) terrain->setShader(&shaderTerrainWinter);
    else if(season == 1) terrain->setShader(&shaderTerrainSpring);
    else if(season == 2) terrain->setShader(&shaderTerrainSummer);
    else terrain->setShader(&shaderTerrainAutumn);

    update();
}

