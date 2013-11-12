#include "weatherstationgui.h"
#include <QApplication>
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
    QApplication a(argc, argv);
    weatherstationgui w;
    w.show();

    cout << "Weather Station Test Pilot Program" << endl;
    // initialization
    weather w_test;
    // load weather data resource
    if (!w_test.loadFile()) { std::cout << "Error Loading File!" << endl; return 0; }
    // prompt for station ID
    string w_id = w_test.promptStationID();
    w_test.setStationList();
    // check validity of input station ID
    w_test.isStationIDValid(w_id);
    // access the weather data record
    weather_data_t test_array = w_test.getRecord();
    // check if data entry is complete
    bool res = w_test.isDataComplete(test_array);
    std::cout << "the result is " << res << endl;
    std::cout << "maxium size of array is " << test_array.max_size() << endl;
    std::cout << "allocated size of array is " << test_array.capacity() << endl;

    // computation section
    computation c_test;																																	// TEST: constructor
    c_test.setDataRecord(test_array);																											// TEST: class member -> data record transfer
    weather_data_t computation_data_record = c_test.getDataRecord();													// TEST: class member -> get private member
    //double data_to_check = atof(computation_data_record[0][2].c_str());
    //std::cout << "the data to check is " << data_to_check << endl;
    //c_test.isDataValid(data_to_check);																										 // TEST: class member -> if an entry is valid
    //std::vector<int> num_valid_data = c_test.numDataValid(computation_data_record);						 // TEST: class member -> number of valid data
    //c_test.numDataInvalid(NUM_DATA_TOTAL, num_valid_data);															 // TEST: class member -> number of invalid data
    //c_test.isLeapYear(data_to_check);																										 // TEST: class member -> leap year determination


    //int column = date_data_map();																												 // TEST: specific weather condition data gather and processing
    //weather_vector_double_t condition_array = condition_vector_prepare(computation_data_record,w_id, "mint", column);
    //double avg_condition = c_test.avgTemp(condition_array);
    //std::cout << "Average condition data is " << avg_condition << endl;

    //weather_vector_double_t max_temp_array = condition_vector_prepare(computation_data_record,w_id, "MT", column);  // TEST: find the maximum temperature of a station
    //double highest_temp = c_test.maxTemp(max_temp_array);  // wrong array fed in; should be station data record array, test later -- M.H
    //std::cout << "The maximum temperature of station " << w_id << " is " << highest_temp << endl;

    //weather_vector_double_t min_temp_array = condition_vector_prepare(computation_data_record,w_id, "mint", column);  // TEST: find the minimum temperature of a station
    //double lowest_temp = c_test.minTemp(min_temp_array);   // wrong array fed in; should be station data record array, test later -- M.H
    //std::cout << "The maximum temperature of station " << w_id << " is " << lowest_temp << endl;

    if (c_test.setStationDataRecord(computation_data_record, w_id) == true )
        std::cout << "Station " << w_id << " weather data record compilation is finished!" << endl;

        ofstream myfile;
     myfile.open ("example.txt");

    weather_data_t station_specific_data = c_test.getStationDataRecord();
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

     int years_of_op = c_test.numYearOperation(station_specific_data);														// TEST: number of years of operation
     std::cout << "Station " << w_id << " has been operating for " << years_of_op << " years " << endl;

    cin.ignore();
    cin.get();
    //return 0;

    return a.exec();
}
