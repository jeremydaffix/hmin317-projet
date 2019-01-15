#include "engine/gameobject.h"

GameObject::GameObject(QVector3D pos, QQuaternion rot, QVector3D sc)
{
    localPosition = pos;
    localRotation = rot;
    localScale = sc;
}

GameObject::~GameObject()
{

}


GameObject *GameObject::getParent() const
{
    return parent;
}

void GameObject::setParent(GameObject *value)
{
    parent = value;
}



std::list<GameObject *> GameObject::getChildren() const
{
    return children;
}

// ajout d'un enfant
void GameObject::addChild(GameObject *child)
{
    if(child->getParent() != NULL) {

        child->getParent()->removeChild(child);
    }

    children.push_back(child);
    child->setParent(this);
}

void GameObject::removeChild(GameObject *child)
{
    //if(std::find(children.begin(), children.end(), child) != children.end()) children.remove(child);
    //if(std::find(children.begin(), children.end(), child) != children.end()) children.erase(std::find(children.begin(), children.end(), child));

    auto pos = std::find(children.begin(), children.end(), child);
    if(pos != children.end())
    {
        children.erase(pos);
    }

    child->setParent(NULL);

    //delete child; // pas à lui de de libérer car on peut très bien juste changer la hiérarchie
}



std::list<Component *> GameObject::getComponents() const
{
    return components;
}

void GameObject::addComponent(Component *c)
{
    if(c->getContainer() != NULL) {

        c->getContainer()->removeComponent(c);
    }

    components.push_back(c);
    c->setContainer(this);
}

void GameObject::removeComponent(Component *c)
{
    c->setContainer(NULL);
    auto pos = std::find(components.begin(), components.end(), c);
    if(pos != components.end()) components.erase(pos);
    delete c; ////
}


// cette méthode est appelée par les createGeometry() des classes qui héritent de GameObject.
// elle définit le comportement par défaut : appeler la création de la géométrie de chaque enfant.
void GameObject::createGeometry()
{
    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->createGeometry();
    }
}

// cette méthode est appelée par les draw() des classes qui héritent de GameObject.
// elle définit le comportement par défaut : appeler l'affichage de chaque enfant.
void GameObject::draw()
{
    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->draw();
    }
}



// pour les composants

void GameObject::update()
{
    // pour tous les composants du gameobject courant

    std::list<Component *> l = getComponents();

    std::list<Component*>::iterator itComp;
    for (itComp = l.begin() ; itComp != l.end(); ++itComp)
    {
        if((*itComp)->getEnabled()) (*itComp)->update(); // on exécute si activé
    }


    // ensuite on passage le message à la suite de la hiérarchie

    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->update();
    }
}

void GameObject::fixedUpdate()
{
    // pour tous les composants du gameobject courant

    std::list<Component *> l = getComponents();

    std::list<Component*>::iterator itComp;
    for (itComp = l.begin() ; itComp != l.end(); ++itComp)
    {
        if((*itComp)->getEnabled()) (*itComp)->fixedUpdate(); // on exécute si activé
    }


    // ensuite on passe le message à la suite de la hiérarchie

    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->fixedUpdate();
    }
}

void GameObject::destroy()
{
    // libération des components
    // (les ressources qu'ils utilisent sont libérées dans leur destructeur)

    std::list<Component *> l = getComponents();

    std::list<Component*>::iterator itComp;
    for (itComp = l.begin() ; itComp != l.end(); ++itComp)
    {
        (*itComp)->setEnabled(false);
        //delete (*itComp);
    }

    components.clear(); // clear() appelle aussi les delete


    // libération des gameobjects enfants

    std::list<GameObject*>::iterator it;
    for (it = children.begin(); it != children.end(); ++it)
    {
        (*it)->destroy();
        //delete (*it);
    }

    children.clear(); // clear() appelle aussi les delete
}

// ***


QVector3D GameObject::getLocalScale() const
{
    return localScale;
}

void GameObject::setLocalScale(const QVector3D &value)
{
    localScale = value;
}


// calcul du scale en prenant en compte la hiérarchie du graphe de scène !
QVector3D GameObject::getScale() const
{
    // scale repère world = multiplication des scales de la hiérarchie

    QVector3D worldScale = getLocalScale();

    GameObject *go = parent;

    while(go != NULL) {

        worldScale *= go->getLocalScale();

        go = go->getParent();
    }

    return worldScale;
}


// déplacer l'objet, non pas dans la direction du repère monde
// mais en prenant en compte sa rotation (+ celles de sa hiérarchie)
void GameObject::move(QVector3D v)
{
    // calculer la rotation / direction

    QQuaternion rot = localRotation;

    GameObject *go = parent;

    while(go != NULL) {

        if(go->getParent() != NULL) rot = go->getLocalRotation() * rot;
        else go->getLocalRotation().inverted() * rot; // racine de la scène

        go = go->getParent();
    }


    QVector3D newV = rot.rotatedVector(v);

    setLocalPosition(localPosition + newV);
}

/*void GameObject::setScale(const QVector3D &value)
{

}*/

// calcul de la matrice de transformation locale
QMatrix4x4 GameObject::getLocalTransform() const
{
    QMatrix4x4 transf;

    transf.translate(getLocalPosition());
    transf.rotate(getLocalRotation());
    transf.scale(getLocalScale());

    return transf;
}


// calcul de la matrice de transformation en prenant en compte la hiérarchie du graphe de scène !
QMatrix4x4 GameObject::getTransform() const
{
    QMatrix4x4 transf = getLocalTransform();

    GameObject *go = parent;

    while(go != NULL) {

        transf = go->getLocalTransform() * transf;

        go = go->getParent();
    }

    return transf;
}

QVector3D GameObject::getLocalPosition() const
{
    return localPosition;
}

void GameObject::setLocalPosition(const QVector3D &value)
{
    localPosition = value;
}


QQuaternion GameObject::getLocalRotation() const
{
    return localRotation;
}

void GameObject::setLocalRotation(const QQuaternion &value)
{
    localRotation = value;
}



