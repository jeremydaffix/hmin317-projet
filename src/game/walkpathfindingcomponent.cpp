#include "walkpathfindingcomponent.h"

WalkPathfindingComponent::WalkPathfindingComponent(GameMap *gm)
{
    gameMap = gm;

}

void WalkPathfindingComponent::update()
{

}

void WalkPathfindingComponent::fixedUpdate()
{

    if(getContainer() != NULL)
    {
        QVector3D pos = getContainer()->getLocalPosition();
        QVector2D cas = gameMap->posToCase(QVector2D(pos.x(), pos.y()));

        QVector2D targetCase = QVector2D(5,4);


        if(path.size() == 0)
        {
            path = gameMap->calcPath(cas, targetCase);

        }


        if(path.size() > 0)
        {
            QVector2D next = path.front();

            //qDebug() << "GO FROM " << cas << " TO " << next;

            QVector2D dir = (next - cas).normalized();

            //qDebug() << "DIST1 " << getContainer()->getLocalPosition().distanceToPoint(gameMap->CaseToPos(next));

            //qDebug() << "DIR " << (next - cas) << " : "<< dir.x() << dir.y();

            getContainer()->setLocalPosition(pos + dir / 100.);

            qDebug() << "DIST2 " << getContainer()->getLocalPosition().distanceToPoint(gameMap->CaseToPos(next));

            if(getContainer()->getLocalPosition().distanceToPoint(gameMap->CaseToPos(next)) < 0.75)
            //if(next == cas)
            {
                qDebug() << "NEXT";
                path.pop_back();
            }


        }
    }


}
