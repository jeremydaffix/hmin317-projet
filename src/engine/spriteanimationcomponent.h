#ifndef SPRITEANIMATIONCOMPONENT_H
#define SPRITEANIMATIONCOMPONENT_H

#include <engine/component.h>
#include <engine/sprite.h>

#include <vector>
#include <qopengltexture.h>


// component pour une animation 2d (= suite de textures affichées dans un sprite)
// possibilité de mettre plusieurs components sur un même sprite,
// qu'on active ou désactive selon l'animation voulue !

class SpriteAnimationComponent : public Component
{
public:
    SpriteAnimationComponent(int _fps = 1, std::vector<QOpenGLTexture *> listTextures = std::vector<QOpenGLTexture *>());
    ~SpriteAnimationComponent();

    void update();
    void fixedUpdate();

    int getFps() const;
    void setFps(int value);

    void addTexture(QOpenGLTexture* t);
    //void removeTexture(QOpenGLTexture* t);
    void clearTextures();

protected:

    int fps;
    std::vector<QOpenGLTexture *> textures;
    int cptFrame = 0;
    int currentTexture = 0;


};

#endif // SPRITEANIMATIONCOMPONENT_H
