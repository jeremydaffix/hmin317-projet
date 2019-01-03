#ifndef EFFECTSPRITECOMPONENT_H
#define EFFECTSPRITECOMPONENT_H


#include <engine/sprite.h>


class EffectSpriteComponent : public Component
{
public:

    static const int TYPE_HIGHLIGHT = 0;
    static const int TYPE_BLINK = 1;

    EffectSpriteComponent(int t, int fr);

    void update();
    void fixedUpdate();

protected:

    Sprite *sprite = NULL;
    int type;
    int frames;
    int cptFrames = 0;

    QOpenGLShaderProgram* initialShader = NULL;
};

#endif // EFFECTSPRITECOMPONENT_H
