#include "weatherstationgui.h"

#include <QApplication>
#include <QFile>
#include <QResource>
#include <QDebug>
#include <QString>
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

    //double data_to_check = atof(computation_data_record[0][2].c_str());
    //std::cout << "the data to check is " << data_to_check << endl;
    //c.isDataValid(data_to_check);																										 // TEST: class member -> if an entry is valid
    //std::vector<int> num_valid_data = c.numDataValid(computation_data_record);						 // TEST: class member -> number of valid data
    //c.numDataInvalid(NUM_DATA_TOTAL, num_valid_data);															 // TEST: class member -> number of invalid data
    //c.isLeapYear(data_to_check);																										 // TEST: class member -> leap year determination

    //int column = date_data_map();
    // TEST: specific weather condition data gather and processing
    weather_vector_double_t avg_condition;
    for (int day = 1; day <= 366; day ++){
        int column = day + 4 - 1;

        weather_vector_double_t condition_array = condition_vector_prepare(computation_data_record,w_id, "MT", column);
        avg_condition.push_back(c.avgTemp(condition_array));
    }
    c.setAvgHighTempVec(avg_condition);
    std::cout << "size is " << c.getAvgHighTempVec().size() << endl;

    //weather_vector_double_t max_temp_array = condition_vector_prepare(computation_data_record,w_id, "MT", column);  // TEST: find the maximum temperature of a station
    //double highest_temp = c.maxTemp(max_temp_array);  // wrong array fed in; should be station data record array, test later -- M.H
    //std::cout << "The maximum temperature of station " << w_id << " is " << highest_temp << endl;

    //weather_vector_double_t min_temp_array = condition_vector_prepare(computation_data_record,w_id, "mint", column);  // TEST: find the minimum temperature of a station
    //double lowest_temp = c.minTemp(min_temp_array);   // wrong array fed in; should be station data record array, test later -- M.H
    //std::cout << "The maximum temperature of station " << w_id << " is " << lowest_temp << endl;

    if (c.setStationDataRecord(computation_data_record, w_id) == true )
        std::cout << "Station " << w_id << " weather data record compilation is finished!" << endl;

        ofstream myfile;
     myfile.open ("example.txt");

    weather_data_t station_specific_data = c.getStationDataRecord();
    std::cout << "size of station vector now is " << station_specific_data.size() << endl;

    //for (size_t row = 0; row < station_specific_data.size(); row++) {
    //	//if (station_specific_data.empty() ) std::cout << "This line is empty!" << endl;
    //	//std::cout << "Station Data => ";
    //	myfile << "Station Data => " << endl;
    //	for (size_t column = 0; column < station_specific_data[row].size(); column++)  {
    //		//std::cout << station_specific_data[row][column] << " ";
    //		myfile  << station_specific_data[row][column] << " ";
    //	}
    //	//std::cout << endl;
    //	myfile << endl;
    //}

     myfile.close();

     int years_of_op = c.numYearOperation(station_specific_data);														// TEST: number of years of operation
     std::cout << "Station " << w_id << " has been operating for " << years_of_op << " years " << endl;

    cin.ignore();
    cin.get();

    /* ******************************** */
    /* plot key indicators on to window */
    QApplication weatherStation(argc, argv);
    weatherstationgui weatherStationGUI;
    weatherStationGUI.show();
    return weatherStation.exec();
}
