#include "component.h"

/*Component::Component()
{

}*/

Component::~Component()
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

bool Component::getEnabled() const
{
    return enabled;
}

void Component::setEnabled(bool value)
{
    enabled = value;
}
