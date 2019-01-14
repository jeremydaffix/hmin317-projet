#include "walkpathfindingcomponent.h"

WalkPathfindingComponent::WalkPathfindingComponent(GameMap *gm)
{
    gameMap = gm;

    targetPos = QVector2D(0,0);
}

void WalkPathfindingComponent::update()
{

}

void WalkPathfindingComponent::fixedUpdate()
{

    if(getContainer() != NULL)
    {
        QVector3D pos = getContainer()->getLocalPosition();
        QVector2D pos2 = QVector2D(pos.x(), pos.y());
        QVector2D cas = gameMap->posToCase(pos2);

        //QVector2D targetCase = QVector2D(5,4);


        if(path.size() == 0) // calcul d'un nouveau chemin
        {
            path = gameMap->calcPath(cas, gameMap->posToCase(targetPos));

        }


        QVector2D dir;

        if(soldier == NULL) soldier = (Soldier*)getContainer();


        if(path.size() > 0) // chemin trouvé
        {
            QVector2D next = path.front();

            /*QVector2D*/ dir = (gameMap->caseToPos(next) - pos2).normalized(); // direction vers la prochaine position du chemin

            getContainer()->setLocalPosition(pos + dir / 150.); // on avance dans cette direction
            soldier->selectStateWalk(dir);

            if((path.size() > 1 && next == cas) || // arrivé dans la case du point suivant
               (getContainer()->getLocalPosition().distanceToPoint(gameMap->caseToPos(next)) < 0.10)) // ou assez proche de ce point
            {
                //qDebug() << "NEXT";
                path.pop_back(); // on passe à la position suivante
            }

        }



        // pathfinding terminé : on finit en se rapprochant en ligne droite de la position précise de la target
        if(path.size() == 0 && getContainer()->getLocalPosition().distanceToPoint(targetPos) > 0.05)
        {
            dir = (targetPos - QVector2D(getContainer()->getLocalPosition().x(), getContainer()->getLocalPosition().y())).normalized();

            getContainer()->setLocalPosition(getContainer()->getLocalPosition() + dir / 150.);
             soldier->selectStateWalk(dir);
        }




        if(path.size() == 0 && getContainer()->getLocalPosition().distanceToPoint(targetPos) <= 0.05)
        {
            //qDebug() << getContainer()->getLocalPosition().distanceToPoint(targetPos);
             //((Soldier*)getContainer())->selectStateLooking(dir);
            //qDebug("FINISHED ! :)");

            soldier->setLife(0);
        }
    }


}



QVector2D WalkPathfindingComponent::getTargetPos() const
{
    return gameMap->posToCase(targetPos);
}

void WalkPathfindingComponent::setTargetPos(const QVector2D &value) // on passe des cases, mais stocké en unités monde
{
    targetPos = gameMap->caseToPos(value);

    path.clear();
}
