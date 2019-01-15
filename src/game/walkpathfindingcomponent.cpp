#include "walkpathfindingcomponent.h"

#include <game/imaginawars.h>


WalkPathfindingComponent::WalkPathfindingComponent(GameMap *gm)
{
    gameMap = gm;
    iw = (ImaginaWars *)ImaginaWars::getInstance();

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

        if(path.size() == 0) // calcul d'un nouveau chemin
        {
            path = gameMap->calcPath(cas, gameMap->posToCase(targetPos));
        }


        QVector2D dir;

        if(soldier == NULL) soldier = (Soldier*)getContainer();


        if(path.size() > 0) // chemin trouvé
        {
            QVector2D next = path.front();

            dir = (gameMap->caseToPos(next) - pos2).normalized(); // direction vers la prochaine position du chemin

            moveTowards(dir);

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

            moveTowards(dir);
        }




        if(path.size() == 0 && getContainer()->getLocalPosition().distanceToPoint(targetPos) <= 0.05)
        {
            //qDebug("FINISHED ! :)");

            soldier->disableAnims();
        }
    }


}



QVector2D WalkPathfindingComponent::getTargetPos() const // position vers laquelle on va (ne change pas même si la target bouge ensuite)
{
    return gameMap->posToCase(targetPos);
}

void WalkPathfindingComponent::setTargetPos(const QVector2D &value) // on passe des cases, mais stocké en unités monde
{
    targetPos = gameMap->caseToPos(value);

    path.clear();
}

bool WalkPathfindingComponent::isPosFree(QVector3D pos)
{
    std::list<Soldier*> soldiers = iw->getSoldiers();
    std::list<Soldier*>::iterator it;

    for (it = soldiers.begin( ); it != soldiers.end(); ++it)
    {
        float dist = (*it)->getLocalPosition().distanceToPoint(pos);

        if((*it) != soldier && dist <= 0.1) return false; // déja quelqu'un trop près
    }

    // MARCHE MAIS ENGENDRE DES QUEUES

    return true; // c'est bon on peut avancer
}


void WalkPathfindingComponent::moveTowards(QVector2D dir)
{
    QVector3D pos = getContainer()->getLocalPosition();
    QVector3D newPos = (pos + dir / 150. * 4.);

    if(isPosFree(newPos)) { // position libre ?

        getContainer()->setLocalPosition(newPos); // on avance dans cette direction

        soldier->selectStateWalk(dir);
    }

    else { // sinon on se pose oklm

        //moveTowards(QVector2D(dir.x(), -dir.y()));
        soldier->disableAnims();
    }
}
