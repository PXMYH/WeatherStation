#include "utilities.h"
#include "computation.h"
#include "calculation.h"
#include "types.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// constructor 
computation::computation() {
}

// destructor
computation::~computation() {
}

// get data from private member vector overall weather record 
bool computation::setDataRecord(weather_data_t data_record) {

	record = data_record;
    // print out what was read in
	//cout << "Local Copy ..." << endl;
	//for (size_t i=0; i<record.size(); ++i){
 //       for (size_t j=0; j<record[i].size(); ++j)
 //           std::cout << record[i][j] << "|"; // (separate fields by |)
 //       std::cout << endl;
 //   }
	if (record.size() != 0)
		return true;
	else 
		return false;
}

// read data from private member vector overall weather record 
weather_data_t computation::getDataRecord(){
	return record;
}

// set station specific weather data record 
bool computation::setStationDataRecord(weather_data_t record, std::string station_id) {

	stationRecord.resize(record.size());
    //size_t station_row = 0;
	for (size_t row = 0; row < record.size(); row ++) {
		stationRecord[row].resize(record[row].size());
		if (record[row][0].compare(station_id) == 0) // station is matched
		{ 
			stationRecord.push_back(record[row]);
			//for (size_t column = 0; column < record[row].size(); column ++) {
			//	stationRecord[station_row].push_back(record[row][column]);   // add the line of matched entry to the 2D vector
			//}
			//station_row++;
		}
	}
	cleanStationDataRecord(station_id);


	//for (size_t row = 0; row < stationRecord.size(); row ++) {
	//	//if (stationRecord[row].empty()) std::cout << "This line is empty!" << endl;
	//	for (size_t column = 0; column < stationRecord[row].size(); column++)  {
	//		std::cout << stationRecord[row][column] << " *";
	//	}
	//}

	
	return true;
}

bool computation::cleanStationDataRecord(std::string station_id){
	// erase empty lines
	for (size_t row = 0; row < stationRecord.size(); row ++) {
        //std::cout << "station id is " << stationRecord[row][0] << endl;
		if (stationRecord[row][0].compare(station_id) !=0) {
            //std::cout << "ROW : " << row << " Deleteing empty line!" << endl;
				stationRecord.erase(stationRecord.begin() + row);
		}
	}
	return true;
}


weather_data_t computation::getStationDataRecord() {
	return stationRecord;
}

// compute number of valid entries
weather_vector_int_t computation::numDataValid(weather_data_t& data_record){
	// declare a vector to store the number of valid data entries information for each record row
	weather_vector_int_t data_valid_num_cnt ;
	int tmp_cnt = 0;

	// sweep through all rows and column 5 to end, validate data entries
	for (size_t row = 0; row < data_record.size(); row ++) // sweep rows
	{
		tmp_cnt = 0;                                                                                                                            // reset counter
		for (size_t column = 4; column < data_record[row].size(); column ++) {                                 // sweep columns
			if (    isDataValid(     atof(    data_record[row][column].c_str()   )    )   )                          // validate data entries
				tmp_cnt ++;																														 // increment counter
		}
		data_valid_num_cnt.push_back(tmp_cnt);
		std::cout << "Valid number of data entry is " << tmp_cnt << endl;
	}
	
	return data_valid_num_cnt;
}

// compute number of invalid entries
weather_vector_int_t computation::numDataInvalid(int num_data_total, weather_vector_int_t  num_data_valid){
	// declare a vector to store the number of invalid data entries information for each record row
	weather_vector_int_t data_invalid_num_cnt;
	for (size_t index = 0; index < num_data_valid.size(); index ++) {
		data_invalid_num_cnt.push_back(num_data_total-num_data_valid[index]);
		cout << "Invalid number of data entry is " << data_invalid_num_cnt[index] << endl;
	}
	return data_invalid_num_cnt;
}

int computation::numYearOperation(weather_data_t& record){
	int num_yr_op = 0;
	int yr =0, yr_prev = 0;
	bool overflow_flag = false;
	// sweep
	for (size_t row = 0; row < record.size(); row ++) {
		
        yr = atoi(record[row][2].c_str());			// store year number
		
		size_t column =0;
		while (!isDataValid(        atof(      record[row][column].c_str()    )    ) ) { // valid data does not exist in a year
			column ++;
			if (column > record[row].size()) {	
				overflow_flag = true;
				break;   
			}
		}
		
		// make sure while loop is not break out due to overflow
		if (overflow_flag == false) {
			if (yr != yr_prev) ++num_yr_op;
			yr_prev = yr;		// register valid year number
		}
	}
	return num_yr_op;
}


// compute average high/low temperature of a station
double computation::avgTemp(weather_vector_double_t TempArray){
	double tmp_temp = 0;																		// initialize temperary temperature counter
	// optimization here, overlapping portion of functionality with numDataValid -- M.H.

	int num_year_operation = 0;
	for (size_t index = 0; index < TempArray.size(); index ++)           // add up all high temperature data readings
	{
		if (isDataValid(TempArray.at(index)))  {
			num_year_operation ++;
			tmp_temp = tmp_temp + TempArray.at(index);
		}
	}
	
	double avg_temp = -100.0;															// initialize average maximum temperature to -100 (unrealistic)
	if (num_year_operation == 0) return avg_temp;
	else return avg_temp = tmp_temp / num_year_operation;
}

// store average high temperature of each day in year information
void computation::setAvgHighTempVec(weather_vector_double_t& avg_high_temp_vec){
    for (size_t i = 0; i < avg_high_temp_vec.size(); i++)
        avgHighTempVec.push_back(avg_high_temp_vec[i]);
}

// get average high temperature of each day in year information
weather_vector_double_t computation::getAvgHighTempVec(){
    return avgHighTempVec;
}

// store average low temperature of each day in year information
void computation::setAvgLowTempVec(weather_vector_double_t& avg_low_temp_vec){
    for (size_t i = 0; i < avg_low_temp_vec.size(); i++)
        avgLowTempVec.push_back(avg_low_temp_vec[i]);
}

// get average low temperature of each day in year information
weather_vector_double_t computation::getAvgLowTempVec(){
    return avgLowTempVec;
}


// determine a leap year
bool computation::isLeapYear(int year){
	// year can be evenly divided by 4
	if (year%4 == 0){
		if (year%100 != 0) {
			std::cout << "Leap Year!" << endl;
			return true; // leap year
		}
		else { // year can be evenly divided by 100
			if (year%400 != 0)
				return false;
			else // year can be evenly divided by 400
				{
					std::cout << "Leap Year!" << endl;
					return true;
				}
		}
	}
	return false;
}

// determine if a data entry is valid value 
bool computation::isDataValid(double data){
	// if data entry is -99999 => invalid
	if (data == -99999) {
        //std::cout << "Invalid Data!" << endl;
		return false;
	} else {
		//std::cout << "Valid Data, proceeding ..." << endl;
		return true;
	}
}

// find the highest temperature of a station
double computation::maxTemp(weather_vector_double_t& TempArray) {
	double high = -99999.0;
	// sweep the vector to get the maximum temperature
	for (size_t index = 0; index < TempArray.size(); index ++)     {     
		if (isDataValid(TempArray.at(index))) 
			if (TempArray.at(index) > high)
				high =  TempArray.at(index);
	}

	// if high is a valid number, then return the value, if not, then return error value (-99999.0)
	return high;
}

// find the lowest temperature of a station
double computation::minTemp(weather_vector_double_t& TempArray) {
	double low = -99999.0;
	// sweep the vector to get the minimum temperature
	for (size_t index = 0; index < TempArray.size(); index ++)     {     
		if (isDataValid(TempArray.at(index))) 
			if (TempArray.at(index) > low)
				low =  TempArray.at(index);
	}

	// if low is a valid number, then return the value, if not, then return error value (-99999.0)
	return low;
}

// set highest temperature date
bool computation::setHighTempDate(int date) {
	highTempDate = date;
	return true;
}

// set lowest temperature date
bool computation::setLowTempDate(int date) {
	lowTempDate = date;
	return true;
}
