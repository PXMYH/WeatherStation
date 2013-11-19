#ifndef WEATHERSTATIONGUI_H
#define WEATHERSTATIONGUI_H

#include "types.h"
#include <QMainWindow>
#include <QWidget>
#include <QPoint>
#include <QPointF>
#include <QVector>
#include <vector>

namespace Ui {
class weatherstationgui;
}

class weatherstationgui : public QMainWindow
{
    Q_OBJECT

public:
    explicit weatherstationgui(QWidget *parent = 0);
    ~weatherstationgui();

    void draw( QVector<QPointF>  dataIn);
    void drawHighTemp (QVector<QPointF>  dataIn);
    void drawLowTemp (QVector<QPointF>  dataIn);

    void setStationID(QString id);
    void setOpYearNum(QString opYearNum);

private:
    Ui::weatherstationgui *ui;

    QVector<QPointF> wellData;
    QVector<QPointF> highTempData;
    QVector<QPointF> lowTempData;
    QString stationID;
    QString opYear;

protected:
    // paint method
    void paintEvent(QPaintEvent *event);
};

#endif // WEATHERSTATIONGUI_H
