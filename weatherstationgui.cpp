#include "weatherstationgui.h"
#include "ui_weatherstationgui.h"

#include "utilities.h"
#include "computation.h"
#include "calculation.h"
#include "types.h"

#include <vector>
#include <QtWidgets>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QFont>
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

void weatherstationgui::draw(QVector<QPointF>  dataIn){
   wellData = dataIn;
   update();
}

void weatherstationgui::drawHighTemp (QVector<QPointF>  dataIn){
    highTempData = dataIn;
    update();
}


void weatherstationgui::drawLowTemp (QVector<QPointF>  dataIn){
    lowTempData = dataIn;
    update();
}

// set weather station ID for plotting
void weatherstationgui::setStationID(QString id){
    stationID = id;
    update();
}

// set number of operating years
void weatherstationgui::setOpYearNum(QString opYearNum){
    opYear = opYearNum;
    update();
}

void weatherstationgui::paintEvent(QPaintEvent *event){

    // create a painter
    QPainter painter(this);

    // coordination transform
    int trans_axis_x = width()/20;
    int trans_axis_y = height()*9/10;

    painter.translate(trans_axis_x,trans_axis_y);

    // set font sizes
    int title_font_size  = width()/35;
    int legend_font_size = width()/80;
    int brief_font_size  = width()/60;

    // plot x and y axis
    QPen axis_pen(Qt::black);                 // axis pen
    axis_pen.setWidth(2);
    painter.setPen(axis_pen);
    painter.drawLine(0, 0, width()*8.5/10, 0);   // x axis
    painter.drawLine(0, 0, 0, -height()*8/10);   // y axis

    // title
    painter.setFont(QFont("Helvetica",title_font_size));     // title pen
    QPen title_pen(Qt::black);
    title_pen.setWidth(5);
    painter.setPen(title_pen);
    QPoint title_pos = QPoint(width()*1/10,-height()*8/10);       // title
    QString title = "Weather Station -- ";
    title.append(stationID);
    painter.drawText(title_pos,title);

    // legend
    painter.setFont(QFont("Helvetica",legend_font_size));      // legend pen
    QPen legend_pen(Qt::black);
    legend_pen.setWidth(2);
    painter.setPen(legend_pen);

    QPoint legend_high_temp_pos = QPoint(width()*5.2/10, -height()*7.5/10);      // high temperature legend
    painter.drawText(legend_high_temp_pos,"RED - Average High Temperature");

    QPoint legend_low_temp_pos = QPoint(width()*5.2/10, -height()*7.5/10+height()/30);   // low temperature legend
    painter.drawText(legend_low_temp_pos,"BLUE - Average Low Temperature");

    // brief
    painter.setFont(QFont("Helvetica",brief_font_size));      // brief pen
    QPen brief_pen(Qt::black);
    brief_pen.setWidth(2);
    painter.setPen(brief_pen);

    QPoint brief_pos = QPoint (width()/10, height()/20);
    QString brief = "This weather station has been operating for ";
    brief.append(opYear);
    brief.append(" years.");
    painter.drawText(brief_pos, brief);

    // draw average high temperature line
    QPen high_temp_pen(Qt::red);
    high_temp_pen.setWidth(3);
    painter.setPen(high_temp_pen);
    painter.drawPolyline(highTempData.data(), static_cast<int>(highTempData.size()));

    // draw average low temperature line
    QPen low_temp_pen(Qt::blue);
    low_temp_pen.setWidth(3);
    painter.setPen(low_temp_pen);
    painter.drawPolyline(lowTempData.data(), static_cast<int>(lowTempData.size()));
}
