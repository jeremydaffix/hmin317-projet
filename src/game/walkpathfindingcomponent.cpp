#include "walkpathfindingcomponent.h"

WalkPathfindingComponent::WalkPathfindingComponent(GameMap *gm)
{
    gameMap = gm;

    targetCase = QVector2D(10,6);
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


        if(path.size() == 0)
        {
            path = gameMap->calcPath(cas, targetCase);

        }


        if(path.size() > 0)
        {
            QVector2D next = path.front();

            //qDebug() << "GO FROM " << cas << " TO " << next;

            //QVector2D dir = (next - cas).normalized();
            QVector2D dir = (gameMap->CaseToPos(next) - pos2).normalized();

            //qDebug() << "DIST1 " << getContainer()->getLocalPosition().distanceToPoint(gameMap->CaseToPos(next));

            getContainer()->setLocalPosition(pos + dir / 150.);

            //qDebug() << "DIST2 " << getContainer()->getLocalPosition().distanceToPoint(gameMap->CaseToPos(next));

            if((path.size() > 1 && next == cas) || (getContainer()->getLocalPosition().distanceToPoint(gameMap->CaseToPos(next)) < 0.10))
            //if(next == cas)
            {
                qDebug() << "NEXT";
                path.pop_back();
            }


        }
    }


}



QVector2D WalkPathfindingComponent::getTargetCase() const
{
    return targetCase;
}

void WalkPathfindingComponent::setTargetCase(const QVector2D &value)
{
    targetCase = value;

    path.clear();
}
