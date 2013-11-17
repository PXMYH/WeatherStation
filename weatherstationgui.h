#ifndef WEATHERSTATIONGUI_H
#define WEATHERSTATIONGUI_H

#include "types.h"
#include <QMainWindow>
#include <QWidget>
#include <QPoint>
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

    // paint method
    void paintEvent(QPaintEvent *event);

    // set/get points vector to be drawn
    void setPoints (weather_vector_double_t&);
    std::vector<QPoint> getPoints();

    friend class weather;
    friend class computation;
private:
    Ui::weatherstationgui *ui;
    std::vector<QPoint> points_weather;

protected:

};

#endif // WEATHERSTATIONGUI_H
