#ifndef WEATHERSTATIONRENDER_H
#define WEATHERSTATIONRENDER_H

#include <QWidget>

class weatherstationrender :public QWidget {
    Q_OBJECT

public: weatherstationrender(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};


#endif
