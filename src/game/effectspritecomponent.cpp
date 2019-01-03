#include "effectspritecomponent.h"


EffectSpriteComponent::EffectSpriteComponent(int t, int fr)
{
    //sprite = (Sprite*)getContainer();
    type = t;
    frames = fr;
}


void EffectSpriteComponent::update()
{

}

void EffectSpriteComponent::fixedUpdate()
{
    if(getContainer() == NULL) return;

    ++cptFrames;


    if(type == TYPE_HIGHLIGHT)
    {

        if(initialShader == NULL) // 1ere frame de l'anim
        {
            sprite = (Sprite*)getContainer();

            //initialShader = sprite->getShader();
            initialShader = ResourcesManager::getInstance()->getGameShader("texturedark");

            sprite->setShader(ResourcesManager::getInstance()->getGameShader("texture"));
        }



    }



    if(cptFrames > frames) // fin de l'animation
    {
        qDebug() << "ESC OVER";
        sprite->setShader(initialShader);
        getContainer()->removeComponent(this); // libéré ensuite par le gameobject
    }


}
