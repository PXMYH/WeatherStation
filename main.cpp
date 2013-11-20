#include "weatherstationgui.h"

#include <QApplication>
#include <QFile>
#include <QResource>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QPointF>
#include <QTextStream>

#include "utilities.h"
#include "computation.h"
#include "calculation.h"
#include "types.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int NUM_DATA_TOTAL = 366;

int main(int argc, char *argv[])
{
    /* *************************************************** */
    /* weather station resource loading and initialization */
    weather w;

    // load weather data resource
    if (!w.loadFile()) {
        std::cout << "Error Loading File!" << endl;
        return 0;
    }

    // access the weather data record
    weather_data_t w_record_array = w.getRecord();

    // remove incomplete weather record
    w.removeIncompleteData(w_record_array);

    // compile valid weather station ID list
    w.setStationList();

    // prompt user for weather station ID to investigate
    std::string w_id = w.promptStationID();

    // check validity of input station ID
    w.isStationIDValid(w_id);




    /* ****************************************** */
    /* weather station key indicators computation */
    computation c;

    // transfer weather data record from class WEATHER to class COMPUTATION
    c.setDataRecord(w_record_array);

    // access private member data record
    weather_data_t computation_data_record = c.getDataRecord();

    // calculate average high / low temperature for a weather station for each day in a year
    weather_vector_double_t avg_high_temp_vec, avg_low_temp_vec;

    for (int day = 1; day <= 366; day ++){
        // map day number into column number in resource file
        int column = day + 4 - 1;

        weather_vector_double_t high_temp_array = condition_vector_prepare(computation_data_record,w_id, "MT", column);
        avg_high_temp_vec.push_back(c.avgTemp(high_temp_array));

        weather_vector_double_t high_low_array = condition_vector_prepare(computation_data_record,w_id, "mint", column);
        avg_low_temp_vec.push_back(c.avgTemp(high_low_array));
    }

    c.setAvgHighTempVec(avg_high_temp_vec);
    c.setAvgLowTempVec(avg_low_temp_vec);


    //weather_vector_double_t max_temp_array = condition_vector_prepare(computation_data_record,w_id, "MT", column);  // TEST: find the maximum temperature of a station
    //double highest_temp = c.maxTemp(max_temp_array);  // wrong array fed in; should be station data record array, test later -- M.H
    //std::cout << "The maximum temperature of station " << w_id << " is " << highest_temp << endl;

    //weather_vector_double_t min_temp_array = condition_vector_prepare(computation_data_record,w_id, "mint", column);  // TEST: find the minimum temperature of a station
    //double lowest_temp = c.minTemp(min_temp_array);   // wrong array fed in; should be station data record array, test later -- M.H
    //std::cout << "The maximum temperature of station " << w_id << " is " << lowest_temp << endl;

    if (c.setStationDataRecord(computation_data_record, w_id) == true )
        std::cout << "Station " << w_id << " weather data record compilation is finished!" << endl;
    weather_data_t station_specific_data = c.getStationDataRecord();

//    ofstream myfile;
//    myfile.open ("example.txt");
//    myfile.close();

    int years_of_op = c.numYearOperation(station_specific_data);														// TEST: number of years of operation
//    std::cout << "Station " << w_id << " has been operating for " << years_of_op << " years " << endl;

//    cin.ignore();
//    cin.get();

    /* ******************************** */
    /* plot key indicators on to window */
    QApplication weatherStation(argc, argv);
    weatherstationgui weatherStationGUI;

    // set weather station ID
    QString gui_id = QString::number( atoi(w_id.c_str()) );
    weatherStationGUI.setStationID(gui_id);

    // set number of operation years
    QString gui_op_yr = QString::number(years_of_op);
    weatherStationGUI.setOpYearNum(gui_op_yr);

    // temperature curve scaling factor
    int time_scale = 3;
    int temp_scale = -10;

    // draw average high temperature into the main window
    int qpoint_size_h = static_cast<int>(c.getAvgHighTempVec().size());
    QVector<QPointF> points_high_temp(qpoint_size_h);
    for(int i=0; i < qpoint_size_h; i++){
       points_high_temp[i].setX(time_scale * i);
       points_high_temp[i].setY(temp_scale * c.getAvgHighTempVec().at(i));
     }
    weatherStationGUI.drawHighTemp(points_high_temp);

    // draw average low temperature into the main window
    int qpoint_size_l = static_cast<int>(c.getAvgLowTempVec().size());
    QVector<QPointF> points_low_temp(qpoint_size_l);
    for(int i=0; i < qpoint_size_l; i++){
       points_low_temp[i].setX(time_scale * i);
       points_low_temp[i].setY(temp_scale * c.getAvgLowTempVec().at(i));
     }
    weatherStationGUI.drawLowTemp(points_low_temp);

    weatherStationGUI.show();
    return weatherStation.exec();
}
