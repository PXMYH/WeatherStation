#include "weatherstationrender.h"
#include <QPainter>

weatherstationrender::weatherstationrender(QWidget *parent) : QWidget(parent) {

}

void RenderArea::paintEvent(QPaintEvent *event) {

    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };

    QPainter painter(this);
    //std::vector<QPoint> points;
    //painter.drawPolyLine(points.data(), static_cast<int>(points.size()));

    painter.drawPoint(points[1]);
}
