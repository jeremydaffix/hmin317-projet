#ifndef EFFECTSPRITECOMPONENT_H
#define EFFECTSPRITECOMPONENT_H


#include <engine/sprite.h>


// classe composant à associer à un Sprite
// permet d'activer un effet graphique
// pour le moment : seulement highlight

class EffectSpriteComponent : public Component
{
public:

    static const int TYPE_HIGHLIGHT = 0;
    static const int TYPE_BLINK = 1;

    EffectSpriteComponent(int t, int fr, QOpenGLShaderProgram* is, QOpenGLShaderProgram* es);

    void update();
    void fixedUpdate();

protected:

    Sprite *sprite = NULL;
    int type;
    int frames;
    int cptFrames = 0;

    QOpenGLShaderProgram* initialShader = NULL;
    QOpenGLShaderProgram* effectShader = NULL;
};

#endif // EFFECTSPRITECOMPONENT_H
