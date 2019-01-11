#include "imaginawars.h"


/*

  TODO

  controles changement buildings
  controles bouger cibles
  generation soldats
  collisions entre soldats (ou du moins les eviter, check si prochain mvt empiète sur qq1)

  classe Building

  ameliorer pathfinding : zigzag, precision arrivee, orientation idle

  classe Player
  component ennemyai
  component humancontroller

  IA ennemi

  IA soldats (component soldierai)
    aller en direction target
    si cible < distance : aller a la plus proche
    si cible < distance attaque : attaquer (ou capture si neutral?)
    sinon continuer vers target initiale

  gestion life (building et soldier)
  couleur life pour reconnaitre joueur

  bonus?

  sons
  musique

  mode p2p (ultérieurement)

 */

ImaginaWars::ImaginaWars(int _fps) : Game(_fps)
{

}

ImaginaWars::~ImaginaWars()
{
    delete player1;
    delete player2;
}


void ImaginaWars::startGame()
{
    qDebug() << "IMAGINA WARS";

    /*GameMap */gm = new GameMap(":/resources/game/maps/test.json");
    gm->setLocalPosition(QVector3D(0.5,0.5,0));
    gm->setShader(ResourcesManager::getInstance()->getGameShader("texturedark"));
    gm->BuildMap();
    GameScene::getInstance()->addChild(gm);

    //gm->calcPath(QVector2D(1, 1), QVector2D(9, 9));


    spr = new Soldier(Soldier::TYPE_KNIGHT, gm, NULL,
                             QVector2D(0, 0),
                             0,
                             QVector2D(0.08, 0.08),
                             ResourcesManager::getInstance()->getGameShader("texturetoon"));



    /*SpriteAnimationComponent *anim = new SpriteAnimationComponent(12);

    for(int i = 0 ; i < 12 ; ++i)
    {
        anim->addTexture(ResourcesManager::getInstance()->getGameTexture("knight_w_sw_" + std::to_string(i)));
    }

    spr->addComponent(anim);*/



    GameScene::getInstance()->addChild(spr);








    GameScene::getInstance()->createGeometry();
    GameScene::getInstance()->setLocalRotation(QQuaternion::fromEulerAngles(0, 0, 0));
    GameScene::getInstance()->setLocalPosition(QVector3D(0,0,15));


}



void ImaginaWars::initShaders()
{
    QOpenGLShaderProgram * shaderTexture = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader.glsl");
    ResourcesManager::getInstance()->addGameShader("texture", shaderTexture);

    QOpenGLShaderProgram * shaderTextureToon = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_toon.glsl");
    ResourcesManager::getInstance()->addGameShader("texturetoon", shaderTextureToon);

    QOpenGLShaderProgram * shaderTextureDark = ResourcesManager::getInstance()->loadShader(":/resources/shaders/vshader.glsl", ":/resources/shaders/fshader_dark.glsl");
    ResourcesManager::getInstance()->addGameShader("texturedark", shaderTextureDark);

    GameScene::getInstance()->setDefaultShader(shaderTexture);
    //GameScene::getInstance()->setDefaultShader(shaderTextureToon);
}

void ImaginaWars::initTextures()
{
    QOpenGLTexture *textureDice = ResourcesManager::getInstance()->loadTexture(":/Resources/Textures/cube.png");
    ResourcesManager::getInstance()->addGameTexture("cube", textureDice);


    // textures units

    loadUnitTextures("knight");


    // tiles

    int nbrTiles = 66;
    for(int i = 1 ; i <= nbrTiles ; ++i)
    {
        QString qs = ((i < 10 ? "0" : "") + std::to_string(i)).c_str();

        ResourcesManager::getInstance()->addGameTexture("medieval_tile_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(":/resources/textures/medievalrtspack/Tile/medievalTile_" + qs + ".png"));
    }


    // batiments

    ResourcesManager::getInstance()->addGameTexture("building_knight",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_17.png")));

    ResourcesManager::getInstance()->addGameTexture("building_horse",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_21.png")));

    ResourcesManager::getInstance()->addGameTexture("building_archer",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_17.png")));

    ResourcesManager::getInstance()->addGameTexture("building_techno",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_20.png")));

    ResourcesManager::getInstance()->addGameTexture("building_tower",
                                                    ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/medievalrtspack/Structure/medievalStructure_22.png")));


    GameScene::getInstance()->setDefaultTexture(textureDice);



    // fonts

   //ResourcesManager::getInstance()->addGameFont("arial", ResourcesManager::getInstance()->loadFont(":/resources/fonts/arial.ttf"));
   //ResourcesManager::getInstance()->addGameFont("gameover", ResourcesManager::getInstance()->loadFont(":/resources/fonts/Game-Over.ttf"));
}



void ImaginaWars::loadUnitTextures(std::string name)
{
    loadAnimTextures(name, "walking", "w");
    loadAnimTextures(name, "looking", "l");
}

void ImaginaWars::loadAnimTextures(std::string unitName, std::string animName, std::string animPrefix)
{
    for(int i = 0 ; i < 12 ; ++i)
    {
        std::string qs = ((i < 10 ? "0" : "") + std::to_string(i)).c_str();


        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_n_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " n00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_ne_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " ne00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_e_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " e00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_se_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " se00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_s_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " s00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_sw_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " sw00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_w_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " w00" + qs + ".png")));

        ResourcesManager::getInstance()->addGameTexture(unitName + "_" + animPrefix + "_nw_" + std::to_string(i),
                                                        ResourcesManager::getInstance()->loadTexture(QString::fromStdString(":/resources/textures/units/" + unitName + "/city/" + animName + " nw00" + qs + ".png")));
    }
}

GamePlayer *ImaginaWars::getPlayer2()
{
    return player2;
}

GamePlayer *ImaginaWars::getPlayer1()
{
    return player1;
}


void ImaginaWars::mouseReleaseEvent(QMouseEvent *e)
{
    //qDebug() << "CLICK " << e->x() << ";" << e->y();


    // il va falloir transformer tout ça dans le repère monde :o

    // merci http://antongerdelan.net/opengl/raycasting.html


    // 2d Viewport Coordinates -> 3d Normalised Device Coordinates

    float x = (2.0f * e->x()) / glWidth - 1.0f;
    float y = 1.0f - (2.0f * e->y()) / glHeight;
    float z = 1.0f;
    QVector3D ray_nds = QVector3D(x, y, z);

    // 4d Homogeneous Clip Coordinates

    QVector4D ray_clip = QVector4D(ray_nds.x(), ray_nds.y(), -1.0, 1.0);


   // 4d Eye (Camera) Coordinates

    QMatrix4x4 proj = GameScene::getInstance()->getProjection();

    QVector4D ray_eye = proj.inverted() * ray_clip;
    ray_eye = QVector4D(ray_eye.x(), ray_eye.y(), -1.0, 0.0);


    // 4d World Coordinates

    //QVector3D ray_wor = (inverse(view_matrix) * ray_eye).xyz;
    QVector4D q = QVector4D(GameScene::getInstance()->getLocalTransform() * ray_eye);
    QVector3D ray_wor = QVector3D(q.x(), q.y(), q.z());
    // don't forget to normalise the vector at some point
    ray_wor = ray_wor.normalized();


   qDebug() << "CLICK WORLD " << ray_wor.x() << ";" << ray_wor.y() << ";" << ray_wor.z();

   // x = +/- 0.55
   // y = +/- 0.33


    //QVector2D cas = gm->posToCase(QVector2D(ray_wor.x() * 20, ray_wor.y() * 20));

   int caseX = (ray_wor.x() + 0.55) / 1.10 * gm->getWidth();
   int caseY =(ray_wor.y() + 0.33) / 0.66 * gm->getHeight();
   if(caseX > gm->getWidth()) caseX = gm->getWidth();
   if(caseX < 0) caseX = 0;
   if(caseY > gm->getHeight()) caseY = gm->getHeight();
   if(caseY < 0) caseY = 0;

   QVector2D cas = QVector2D(caseX, caseY);


    qDebug() << "CLICKED CASE " << cas;

    //pathfinding->setTargetPos(cas);


    spr->getPathfinding()->setTargetPos(QVector2D(ray_wor.x() * 20, ray_wor.y() * 12));

    gm->getSprite(cas)->addComponent(new EffectSpriteComponent(EffectSpriteComponent::TYPE_HIGHLIGHT, 60 * 1));

}


