#ifndef WEATHERSTATIONGUI_H
#define WEATHERSTATIONGUI_H

#include <QMainWindow>

namespace Ui {
class weatherstationgui;
}

class weatherstationgui : public QMainWindow
{
    Q_OBJECT

public:
    explicit weatherstationgui(QWidget *parent = 0);
    ~weatherstationgui();

private:
    Ui::weatherstationgui *ui;
};

#endif // WEATHERSTATIONGUI_H
