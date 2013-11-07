#include "weatherstationgui.h"
#include "ui_weatherstationgui.h"

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
