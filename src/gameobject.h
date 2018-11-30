#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <iostream>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QImage>

#include <component.h>


// Classe représentant un GameObject.
// Tous les objets de la scène sont des GameObject, de la scène / caméra, aux
// objets 3D, en passant par les sprites.
// La classe mère GameObject contient tout ce qui est commun à ces différents objets du graph de scène :
// changements de repères, calcul des positions / rotations / tailles, modification de l'arbre du graphe de scène
// (ajout / suppression d'enfants,...), déplacements dans le bon repère, gestion des composants,...
// L'arbre du graph de scène est implémenté par l'intermédiaire d'un Pattern composite : chaque GameObject a
// un parent, et une liste d'enfants, de type GameObject.
//
// Chaque classe héritée de GameObject devra notamment redéfinir 2 méthodes :
// createGeometry(), qui créent les sommets nécessaires
// draw(), qui s'occupe d'afficher l'objet, à la bonne position / rotation / scale,
// dans le bon repère en prenant en compte la hiérarchie / l'arbre du graphe de scène.
class GameObject
{
public:
    GameObject(QVector3D pos = QVector3D(), QQuaternion rot = QQuaternion(), QVector3D sc = QVector3D(1, 1, 1));
    virtual ~GameObject();


    QVector3D getLocalPosition() const;
    void setLocalPosition(const QVector3D &value);

    QQuaternion getLocalRotation() const;
    void setLocalRotation(const QQuaternion &value);

    QVector3D getLocalScale() const;
    void setLocalScale(const QVector3D &value);

    QVector3D getScale() const;
    //void setScale(const QVector3D &value);


    void move(QVector3D v);


    virtual QMatrix4x4 getLocalTransform() const;
    QMatrix4x4 getTransform() const;


    GameObject *getParent() const;
    void setParent(GameObject *value);




    // gestion enfants
    std::list<GameObject *> getChildren() const;
    void addChild(GameObject* child);
    void removeChild(GameObject* child);

    // gestion composants
    std::list<Component *> getComponents() const;
    void addComponent(Component* c);
    void removeComponent(Component* c);


    // comportement par défaut : appeler les createGeometry() et les draw() des enfants !
    // à redéfinir ensuite dans chaque classe fille
    virtual void createGeometry();
    virtual void draw();



    virtual void update();
    virtual void fixedUpdate();



protected:
    QVector3D localPosition;
    QQuaternion localRotation;
    QVector3D localScale;

    GameObject* parent = NULL;
    std::list<GameObject*> children; // pattern composite :o

    std::list<Component*> components;
};



struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};


#endif // GAMEOBJECT_H
