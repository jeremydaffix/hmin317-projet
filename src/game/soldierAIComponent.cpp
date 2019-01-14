
#include "game/soldierAIComponent.h"

SoldierAIComponent::SoldierAIComponent()
{

}

void SoldierAIComponent::update()
{

}

void SoldierAIComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;




    ++cptFrames;
}
