#include "objet3d.h"

Objet3d::Objet3d(QVector3D pos, QQuaternion rot, QVector3D sc, QOpenGLShaderProgram* sh) : Model3D (pos, rot, sc, sh)
{
    path = (char*)malloc(sizeof(char)*1024);

}

bool Objet3d:: loadobj(vector <QVector3D> & out_vertices, vector <QVector3D> & out_normals){

    vector< unsigned int > vertexIndices, normalIndices;
    vector<QVector3D> temp_vertices;
    vector< QVector3D> temp_normals;
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            printf("Impossible to open the file !\n");
            return false;
    }

    QTextStream in(&file);

    QString type;
    char separator;

    while(!in.atEnd()){
        in >> type;
        if ( type == "v"){
            QVector3D vertex;
            float x,y,z;
            in >> x >> y >> z;
            vertex.setX(x);
            vertex.setY(y);
            vertex.setZ(z);
            temp_vertices.push_back(vertex);
        }else if (type == "vn"){
            QVector3D normal;
            float x,y,z;
            in >> x >> y >> z;
            normal.setX(x);
            normal.setY(y);
            normal.setZ(z);
            temp_normals.push_back(normal);
        }else if ( type == "f" ){
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], normalIndex[3];
            in >> vertexIndex[0] >> separator >> separator >> normalIndex[0] >>
            vertexIndex[1] >> separator >> separator >> normalIndex[1] >>
            vertexIndex[2] >> separator >> separator >> normalIndex[2];
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    for( unsigned int i=0; i < vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        QVector3D vertex = temp_vertices[ vertexIndex-1 ];
        out_vertices.push_back(vertex);
    }
    for( unsigned int i=0; i < normalIndices.size(); i++ ){
        unsigned int normalIndex = normalIndices[i];
        QVector3D normals = temp_normals[ normalIndex-1 ];
        out_normals.push_back(normals);
    }

    file.close();
    return true;
}

void Objet3d:: createGeometry(){

    if(!VBO.create())
        {
            std::cerr << "Error creating VBO" << std::endl;
        }

        if(!VBO.bind())
        {
            std::cerr << "Error binding array buffer" << std::endl;
        }

    vector<QVector3D> sommet;
    vector<QVector3D> normals;
    vector<GLushort> indices;
    bool res = loadobj(sommet,normals);
    for(int i = 0; i < sommet.size(); i++){
        indices.push_back(i);
    }


    //VBO0

    taille = indices.size();
    VBO.allocate(sommet.data(), sommet.size() * sizeof(QVector3D));
   /* arrayBuf.bind();
    arrayBuf.allocate(sommet.data(),sommet.size()* sizeof(QVector3D));


    //VBO1
    taille = indices.size();
    indexBuf.bind();
    indexBuf.allocate(indices.data(), indices.size() * sizeof(GLushort));*/


}
void Objet3d::draw(){
    GameObject::draw(); // affichage enfants


    if(shader == NULL) shader = GameScene::getInstance()->getDefaultShader();

    if (!shader->bind())
            return;

    QMatrix4x4 matrix = getTransform(); // transform dans le repère monde

    shader->setUniformValue("mvp_matrix", GameScene::getInstance()->getProjection() * matrix);

    if(!VBO.bind())
        {
            std::cerr << "Error binding array buffer" << std::endl;
        }

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = shader->attributeLocation("a_position");
        shader->enableAttributeArray(vertexLocation);
        shader->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

        // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
        int texcoordLocation = shader->attributeLocation("a_texcoord");
        shader->enableAttributeArray(texcoordLocation);
        shader->setAttributeBuffer(texcoordLocation, GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

        glDrawArrays(GL_TRIANGLES, 0, taille);

}
