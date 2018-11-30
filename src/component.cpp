#include "component.h"

Component::Component()
{

}

GameObject *Component::getContainer() const
{
    return container;
}

void Component::setContainer(GameObject *value)
{
    container = value;
}
