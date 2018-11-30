#ifndef COMPONENT_H
#define COMPONENT_H

//#include<gameobject.h>
#include <iostream>

class GameObject;

// Classe représentant un composant, associé à un GameObject
// A intervalle régulier, les update() et fixedUpdate() de tous
// les composants de tous les GameObject sont appelés
// EN COURS DE DEV
class Component
{
public:
    Component();

    virtual void update() = 0;
    virtual void fixedUpdate() = 0;


    GameObject *getContainer() const;
    void setContainer(GameObject *value);

protected:

    GameObject* container = NULL;
};

#endif // COMPONENT_H
