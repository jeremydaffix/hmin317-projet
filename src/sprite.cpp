#include "sprite.h"


Sprite::Sprite(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh, QOpenGLTexture *tex) : Model3D (pos, rot, sc, sh, tex)
{
}


Sprite::Sprite(QString path, QVector2D pos, float rot, QVector2D sc, QOpenGLShaderProgram* sh)
{

}


void Sprite::createGeometry()
{
    float size = 16. / nbrVertices; // même taille quel que soit le nombre de sommet
    float centerOffset = (nbrVertices - 1) * size / 2.; // pour que le plan soit centré sur sa position

    int nbrFaces = nbrVertices - 1;
    int nbrIndices = (nbrFaces * nbrFaces * 6) + (nbrFaces * 4);

    VertexData vertices[nbrVertices * nbrVertices]; // tableau des sommets

    // pour tous les sommets
    for(int i = 0 ; i < nbrVertices ; ++i) { // ligne

        for(int j = 0 ; j < nbrVertices ; ++j) { // colonne

            // on remplit ligne par ligne

            int pos = i * nbrVertices + j;

            vertices[pos].position = QVector3D((float)j * size - centerOffset, (float)i * size - centerOffset, 0.0);

            vertices[pos].texCoord = QVector2D(1. / nbrFaces * j, 1. / nbrFaces * i);

        }
    }



    GLushort indices[nbrIndices];

    int pos = 0;

    // pour toutes les cases (15 x 15)
    // 2 triangles à afficher
    for(GLushort i = 0 ; i < nbrFaces ; ++i) { // ligne

        for(GLushort j = 0 ; j < nbrFaces ; ++j) { // colonne

            // trangle haut gauche
            GLushort index1 = i * nbrVertices + j; // haut gauche
            GLushort index2 = index1 + 1; // haut droit
            GLushort index3 = index1 + nbrVertices; // bas gauche

            // triangle bas droit
            GLushort index4 = index3; // bas gauche
            GLushort index5 = index3 + 1; // bas droit
            GLushort index6 = index2; // haut droit

            indices[pos++] = index1;
            indices[pos++] = index2;
            indices[pos++] = index3;

            indices[pos++] = index4;
            indices[pos++] = index5;
            indices[pos++] = index6;

            // sur une même ligne, on se retrouve au 1er point de la case suivante en haut à gauche
        }

        // changement de ligne
        /*if(i != (nbrFaces - 1))*/ {

            indices[pos++] = i * nbrVertices + nbrVertices;
            indices[pos++] = i * nbrVertices; // déplacement à gauche
            indices[pos++] = i * nbrVertices;
            indices[pos++] = (i + 1) * nbrVertices; // déplacement d'une ligne
        }
    }

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, nbrVertices * nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, nbrIndices * sizeof(GLushort));

}


void Sprite::draw()
{
    if(shader == NULL) shader = GameScene::getInstance()->getDefaultShader();
    if(texture == NULL) texture = GameScene::getInstance()->getDefaultTexture();

    if (!shader->bind())
            return;

    texture->bind();

    QMatrix4x4 matrix = getTransform(); // transform dans le repère monde

    shader->setUniformValue("mvp_matrix", GameScene::getInstance()->getProjection() * matrix);




    int nbrFaces = nbrVertices - 1;
    int nbrIndices = (nbrFaces * nbrFaces * 6) + (nbrFaces * 4);

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = shader->attributeLocation("a_position");
    shader->enableAttributeArray(vertexLocation);
    shader->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = shader->attributeLocation("a_texcoord");
    shader->enableAttributeArray(texcoordLocation);
    shader->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw plane geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, nbrIndices, GL_UNSIGNED_SHORT, 0);
}
