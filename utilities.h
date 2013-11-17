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
    void removeIncompleteData(weather_data_t&);

    // get/set weather record array
    weather_data_t getRecord();
    void setRecord(weather_data_t&);
	
	// add sort and filter unique station value method here later -- M.H

    // define friend class
    friend class computation;
    friend class weatherstationgui;

private:
    int year;
	std::string station_ID;
	std::string station_name;
	std::string weather_condition;
	weather_data_t record;
    weather_vector_str_t station_list;
};

#endif
