
#include "gridmainwidget.h"

GridMainWidget::GridMainWidget(QWidget *parent) : QWidget(parent)
 {

      gridLayout = new QGridLayout();


       widget1 = new MainWidget(1, 0);
       widget10 = new MainWidget(10, 1);
       widget100 = new MainWidget(100, 2);
       widget1000 = new MainWidget(1000, 3);

       gridLayout->addWidget(widget1, 0, 0);
       gridLayout->addWidget(widget10, 0, 1);
       gridLayout->addWidget(widget100, 1, 0);
       gridLayout->addWidget(widget1000, 1, 1);


      setMinimumSize(QSize(1024,768));

      delete(layout());
      setLayout(gridLayout);

      show();

      widget1000->show();
  }
