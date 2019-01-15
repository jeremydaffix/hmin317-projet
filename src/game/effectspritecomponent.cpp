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

            sprite->setShader(effectShader); // shader de highlight

            //qDebug() << "EFFECT SHADER" << effectShader;
        }


    }



    if(cptFrames > frames) // fin de l'animation
    {
        //qDebug() << "ESC OVER";
        sprite->setShader(initialShader); // on remet le shader initial
        getContainer()->removeComponent(this); // libéré ensuite par le gameobject
    }


}
