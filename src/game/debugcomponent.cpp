#include "debugcomponent.h"

DebugComponent::DebugComponent()
{

}

void DebugComponent::update()
{

}

void DebugComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;


    if(cptFrames % (60 * 5) == 0)
    {
        qDebug() << "***";
        qDebug() << "DBG COMP CONT " << getContainer()->getParent()->getLocalPosition();
        qDebug() << "DBG COMP " << getContainer()->getLocalPosition();
    }


    ++cptFrames;
}
