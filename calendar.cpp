#include "calendar.h"

Calendar::Calendar(MainWidget *w1, MainWidget *w2, MainWidget *w3, MainWidget *w4, QObject *parent) : QObject(parent)
{
    widget1 = w1;
    widget2 = w2;
    widget3 = w3;
    widget4 = w4;

    timerSeason.start(100, this); // 1j = 100ms
}


// un jour est passé
void Calendar::timerEvent(QTimerEvent *e)
{
    // changement de saison :
    // envoi d'un message à chaque fenêtre

    if(currentDay == 92) {

        widget1->setSeason(0);
        widget2->setSeason(1);
        widget3->setSeason(2);
        widget4->setSeason(3);
    }

    else if (currentDay == 183) {

        widget1->setSeason(1);
        widget2->setSeason(2);
        widget3->setSeason(3);
        widget4->setSeason(0);
    }

    else if (currentDay == 274) {

        widget1->setSeason(2);
        widget2->setSeason(3);
        widget3->setSeason(0);
        widget4->setSeason(1);
    }

    else if (currentDay == 0) {

        widget1->setSeason(3);
        widget2->setSeason(0);
        widget3->setSeason(1);
        widget4->setSeason(2);
    }

    currentDay = (currentDay + 1) % 365; // jour + 1


    //qDebug() << "CHANGEMENT SAISON";
}
