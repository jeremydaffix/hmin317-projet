#include "spriteanimationcomponent.h"


SpriteAnimationComponent::SpriteAnimationComponent(int _fps, std::list<QOpenGLTexture *> listTextures)
{
    fps = _fps;
    textures = listTextures;
}


SpriteAnimationComponent::~SpriteAnimationComponent()
{
    ((Sprite*)getContainer())->setTexture(NULL); // pour ne pas détruire la texture courante 2 fois


    // libération des textures

    std::list<QOpenGLTexture*>::iterator it;
    for (it = textures.begin(); it != textures.end(); ++it)
    {
        delete (*it);
    }
}

void SpriteAnimationComponent::update()
{
}

void SpriteAnimationComponent::fixedUpdate()
{


}

int SpriteAnimationComponent::getFps() const
{
    return fps;
}

void SpriteAnimationComponent::setFps(int value)
{
    fps = value;
}

void SpriteAnimationComponent::addTexture(QOpenGLTexture *t)
{
    textures.push_back(t);
}

void SpriteAnimationComponent::removeTexture(QOpenGLTexture *t)
{
    if(std::find(textures.begin(), textures.end(), t) != textures.end()) textures.remove(t);
}

void SpriteAnimationComponent::clearTextures()
{
    textures.clear();
}

