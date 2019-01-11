#include "effectspritecomponent.h"


EffectSpriteComponent::EffectSpriteComponent(int t, int fr, QOpenGLShaderProgram* is, QOpenGLShaderProgram* es)
{
    //sprite = (Sprite*)getContainer();
    type = t;
    frames = fr;

    initialShader = is;
    effectShader = es;


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

        //if(initialShader == NULL) // 1ere frame de l'anim
        if(cptFrames <= 1)
        {
            sprite = (Sprite*)getContainer();

            //initialShader = sprite->getShader();
            //initialShader = ResourcesManager::getInstance()->getGameShader("texturedark");

            //sprite->setShader(ResourcesManager::getInstance()->getGameShader("texture"));
            sprite->setShader(effectShader);

            //qDebug() << "EFFECT SHADER" << effectShader;
        }


    }



    if(cptFrames > frames) // fin de l'animation
    {
        //qDebug() << "ESC OVER";
        sprite->setShader(initialShader);
        getContainer()->removeComponent(this); // libéré ensuite par le gameobject
    }


}
