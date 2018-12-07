#ifndef SPRITEANIMATIONCOMPONENT_H
#define SPRITEANIMATIONCOMPONENT_H

#include <component.h>
#include <sprite.h>

#include <list>
#include <qopengltexture.h>


// component pour une animation 2d (= suite de textures affichées dans un sprite)
// possibilité de mettre plusieurs components sur un même sprite,
// qu'on active ou désactive selon l'animation voulue !

class SpriteAnimationComponent : public Component
{
public:
    SpriteAnimationComponent(int _fps = 1, std::list<QOpenGLTexture *> listTextures = std::list<QOpenGLTexture *>());
    ~SpriteAnimationComponent();

    void update();
    void fixedUpdate();

    int getFps() const;
    void setFps(int value);

    void addTexture(QOpenGLTexture* t);
    void removeTexture(QOpenGLTexture* t);
    void clearTextures();

protected:

    int fps;
    std::list<QOpenGLTexture *> textures;


};

#endif // SPRITEANIMATIONCOMPONENT_H
