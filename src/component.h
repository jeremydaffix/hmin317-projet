#ifndef COMPONENT_H
#define COMPONENT_H

//#include<gameobject.h>
#include <iostream>

class GameObject;

// Classe représentant un composant, associé à un GameObject
// A intervalle régulier, les update() et fixedUpdate() de tous
// les composants de tous les GameObject sont appelés
class Component
{
public:
    //Component();
    virtual ~Component();

    virtual void update() = 0;
    virtual void fixedUpdate() = 0;


    GameObject *getContainer() const;
    void setContainer(GameObject *value);

    bool getEnabled() const;
    void setEnabled(bool value);

protected:

    GameObject* container = NULL;
    bool enabled = true;
};

#endif // COMPONENT_H
