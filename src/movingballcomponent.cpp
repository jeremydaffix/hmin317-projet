#include "movingballcomponent.h"

MovingBallComponent::MovingBallComponent()
{
    direction = QVector2D(1., 1.);
}

void MovingBallComponent::update()
{
    //qDebug("BALL UPDATE");
}

void MovingBallComponent::fixedUpdate()
{
    //qDebug("BALL FIXEDUPDATE");

    QVector3D pos = getContainer()->getLocalPosition();

    if(pos.x() < -5) direction.setX(1.);
    if(pos.x() > 5) direction.setX(-1.);
    if(pos.y() < -5) direction.setY(1.);
    if(pos.y() > 5) direction.setY(-1.);



    getContainer()->setLocalPosition(pos + direction / 20.);

}
