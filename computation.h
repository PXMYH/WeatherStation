#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <vector>
#include "types.h"

class computation {

public:
	computation();																									// constructor
	~computation();																									// destructor
	bool setDataRecord(weather_data_t);																// write data record to private member weather record vector
	weather_data_t getDataRecord();																		// read data record to private member weather record vector
	bool setStationDataRecord(weather_data_t, std::string);									// compile data record for identified weather station
	weather_data_t getStationDataRecord();															// read data record for identified weather station
	

	// not suitable for station_name/station_ID/weather_condition check
	bool isDataValid(double);																					// check valid/invalid data entries
	weather_vector_int_t numDataValid(weather_data_t&);									// compute number of valid entries
	weather_vector_int_t numDataInvalid(int, weather_vector_int_t);					// compute number of invalid entries
	int numYearOperation(weather_data_t&);														// compute number of year a station is operating

	double avgTemp(weather_vector_double_t);													// compute average high/low temperature
	bool isLeapYear(int);																							// determine a leap year
	double maxTemp(weather_vector_double_t&);													// find the highest temperature
	double minTemp(weather_vector_double_t&);													// find the lowest temperature
	

	// get private member record						
	bool setHighTempDate(int);																					// set private member variable highest temperature date
	bool setLowTempDate(int);																					// set private member variable lowest temperature date

	// define friend class
	friend class weather;																							

private:
	weather_data_t record;
	weather_data_t stationRecord;
	int highTempDate;
	int lowTempDate;

	bool cleanStationDataRecord(std::string);
};

#endif