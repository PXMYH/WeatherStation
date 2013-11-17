#include "weatherstationgui.h"
#include "ui_weatherstationgui.h"

#include "utilities.h"
#include "computation.h"
#include "calculation.h"
#include "types.h"

#include <vector>
#include <QtWidgets>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QDebug>

weatherstationgui::weatherstationgui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::weatherstationgui)
{
    ui->setupUi(this);
}

weatherstationgui::~weatherstationgui()
{
    delete ui;
}

void weatherstationgui::paintEvent(QPaintEvent *event){

    qDebug ("I am in!");

    std::vector<QPoint> draw_points = getPoints();
    std::cout << "Point size is " << draw_points.size() << endl;

    // create a painter
    QPainter painter(this);



//    for (size_t index = 0; index < points.size(); index ++) {
//        draw_points[index].setX(100);
//        draw_points[index].setY(100);
//    }

//    static const QPoint points[4] = {
//        QPoint(110, 80),
//        QPoint(230, 10),
//        QPoint(80, 320),
//        QPoint(190, 70)
//    };

    QPen linePen(Qt::red);
    linePen.setWidth(4);

//    painter.setPen(linePen);
//    painter.drawLine(10, 10, 100, 100);
//    painter.drawPoint(points[0]);
//    painter.drawPoint(points[1]);
//    painter.drawPoint(points[2]);
//    painter.drawPoint(points[3]);
    painter.drawPoint(draw_points[0]);
}


void weatherstationgui::setPoints (weather_vector_double_t& points_trans){
    std::cout << "Point size is " << points_trans.size() << endl;
    for (size_t index = 0; index < points_trans.size(); index ++){
        //points_weather.data();
        points_weather[index].setX(index);
        points_weather[index].setY(points_trans.at(index));
    }

}

std::vector<QPoint> weatherstationgui::getPoints(){
    return points_weather;
}
