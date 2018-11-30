#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"

#include <QMainWindow>
#include <QGridLayout>

// Classe représentant un widget qui contient un layout grid avec 4 MainWidget
// au final nous ne l'utilisons pas, car les événements claviers ne sont pas transmis aux MainWidget
class GridMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridMainWidget(QWidget *parent = nullptr);

protected:

    QGridLayout* gridLayout;
    MainWidget *widget1, *widget10, *widget100, *widget1000;

signals:

public slots:
};

#endif // MAINWINDOW_H
