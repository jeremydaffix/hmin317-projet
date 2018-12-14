#include "spriteanimationcomponent.h"


SpriteAnimationComponent::SpriteAnimationComponent(int _fps, std::vector<QOpenGLTexture *> listTextures)
{
    fps = _fps;
    textures = listTextures;
}


SpriteAnimationComponent::~SpriteAnimationComponent()
{
    ((Sprite*)getContainer())->setTexture(NULL); // pour ne pas détruire la texture courante 2 fois


    // libération des textures

    std::vector<QOpenGLTexture*>::iterator it;
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
    if(cptFrame % (60 / fps) == 0)
    {
        ((Sprite*)getContainer())->setTexture(textures[currentTexture]);

        ++currentTexture;
        if(currentTexture >= textures.size())
            currentTexture = 0;
    }

    ++cptFrame;
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

/*void SpriteAnimationComponent::removeTexture(QOpenGLTexture *t)
{
    if(std::find(textures.begin(), textures.end(), t) != textures.end()) textures.remove(t);
}*/

void SpriteAnimationComponent::clearTextures()
{
    textures.clear();
}

