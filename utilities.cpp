#include "utilities.h"
#include "computation.h"
#include "calculation.h"
#include "types.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>    // std::unique, std::distance

using namespace std;

// declaring constants
const int NUM_STATION_LIST = 1948;

// constructor
weather :: weather () {
    // initialize weather record vector
    for (size_t row = 0; row < record.size(); row ++) {
        for (size_t column = 0; column < record[row].size(); column ++)
            record[row][column] = "-9999.0";
    }
}

// destructor 
weather :: ~weather() {
    // delete weather record vector and free up memory
    weather_data_t tmp;
    weather_data_t().swap(tmp);
}

// prompt for user to imput station ID
string weather::promptStationID () {
    std::cout << "Please type in weather station ID for detailed report: ";
	cin >> station_ID;
    std::cout << "Weather Station ID is => " << station_ID << endl;
	return station_ID;
}

// check user typed in station ID is valid
bool weather::isStationIDValid (string id) {
	for (size_t index = 0; index < station_list.size(); index ++)
		// compare with the station ID in the database
		if (id.compare(station_list.at(index))  == 0 ){
			std::cout << "Station ID valid. Report Initialization Starting ..." << endl;
			return true;
		}
	std::cout << "Station ID Invalid! Report Initialization FAILED!" << endl;
	return false;
}

// compile unique weather station IDs
bool weather::setStationList(){
	
    std::cout << "Compiling Station ID List ..." << endl;

	weather_data_t weather_resource_data = getRecord();

    // compile a preliminary station ID list
	for (size_t row = 0; row < weather_resource_data.size(); row ++) {
		station_list.push_back(weather_resource_data[row][0]);
	}

    // sort and remove redundant station IDs
    std::sort (station_list.begin(), station_list.end());
    std::vector<std::string>::iterator it;
    it = std::unique (station_list.begin(), station_list.end());
    station_list.resize( std::distance(station_list.begin(),it) );

    std::cout << "Station ID List Compiled." << endl;

	return true;
}

//  reading the CSV data entries into 2D Vectors
bool weather::loadFile () {

    // csv resource file path
    string weather_data_src = "X:\\Dev\\C++\\WeatherStation\\BCnorthWeatherData.csv";  // replace this absolute path with a relative path for portability

    ifstream file_handle(weather_data_src.c_str());
    if (!file_handle) {
        std::cout << "File can NOT be loaded!" << endl;
        return false;
    }

    // load data into 2D vector
    std::cout << "LOADING DATA ..." << endl;

	string line, field;
    vector<string> data; // row data entry

	// get next line in file
    while ( getline(file_handle,line) ) {
        data.clear();
        stringstream ss(line);

		// break line into comma delimitted fields
        while (getline(ss,field,','))  {
            data.push_back(field);  // add each field to the 1D array
        }

        record.push_back(data);  // add the 1D array to the 2D array
    }
    std::cout << "DATA LOADED." << endl;

    // close weather source data
    file_handle.close();

	return true;
}

// access weather record information
weather_data_t  weather::getRecord(){
	return record;
}

// set weather record vector
void weather::setRecord(weather_data_t& new_record) {
    record = new_record;
}

// remove incomplete record
void weather::removeIncompleteData(weather_data_t& record){

    // sweep each row of record
    size_t row = 0;
    size_t row_max = record.size();
    while (row < row_max) {
        if (record[row].size() != 370) {
                record.erase(record.begin() + row);  // delete incomplete row
            row_max --;
        }
        row ++;
    }

    // update weather record vector
    setRecord(record);
}

