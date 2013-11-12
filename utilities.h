#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include "types.h"

class weather {
public:
   
	weather();																									 // constructor
    ~weather();																									// destructor

	std::string promptStationID ();																	// prompt user for inputting station ID to check weather report
	bool isStationIDValid(std::string);																// check if station ID is valid (in the station ID list database)
	bool loadFile();																							// load weather data resource file
	bool setStationList();																					// compile station ID list database
	bool isDataComplete(weather_data_t&);													// check if data entries are complete, i.e. 370 columns each row
	weather_data_t getRecord();																		// access private member weather data record
	
	// add sort and filter unique station value method here later -- M.H

	friend class computation;																			// define friend class 

private:
	int test;
	std::string station_ID;
	int year;
	std::string station_name;
	std::string weather_condition;
	weather_data_t record;
	std::vector<std::string> station_list;
};

#endif