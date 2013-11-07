#include "weatherstationgui.h"
#include <QApplication>
#include "utilities.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Weather Station Test Pilot Program" << endl;
    QApplication a(argc, argv);
    weatherstationgui w;
    w.show();

    //weather w_test(11);
    //w_test.load_file();
    //cin.get();
    return a.exec();
}
