#ifndef CALENDAR_H
#define CALENDAR_H

#include <QBasicTimer>
#include <QObject>
#include <QDebug>

#include <mainwidget.h>

// Classe pour simuler un déroulement des jours, et des saisons
// L'objet connait 4 MainWidget qui afficheront chacun une saison différente,
// et leur envoie chacun un message avec la saison à afficher
// (ce qui se concrètise de leur côté en changeant le shader du terrain)
class Calendar : public QObject
{
    Q_OBJECT
public:
    explicit Calendar(MainWidget *w1, MainWidget *w2, MainWidget *w3, MainWidget *w4, QObject *parent = nullptr);

signals:

public slots:

protected:

    QBasicTimer timerSeason;
    void timerEvent(QTimerEvent *e) override; // événement appelé toutes les X ms
    int currentDay = 0; // jour courant, de 0 à 364

    MainWidget *widget1, *widget2, *widget3, *widget4; // 1 widget = 1 saison

};

#endif // CALENDAR_H
