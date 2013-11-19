#include "utilities.h"
#include "computation.h"
#include "calculation.h"
#include "types.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


// Function to map date input by user to weather record entry column number 
// date format:
int date_data_map (int month, int day) {

    //int month,day;
    int day_per_month, column;
//	std::cout << "Which date you want to investigate?"<< endl;
//	std::cout << "Month (01/02 etc.):" << endl;
//	std::cin >> month;
//	std::cout << "Your input month is " << month << endl;
//	std::cout << "Day(10/20 etc.)" << endl;
//	std::cin >> day;
//	std::cout << "Your input day is " << day << endl;

	// date mapping to column
	switch (month){
	case 1 : day_per_month = 31; break;
	case 2: day_per_month = 29; break; // this is so due to the way Envrionment Canada compiled its resource data file, column 64 is always February 29, no matter if it exists
	case 3: day_per_month = 31; break;
	case 4: day_per_month = 30; break;
	case 5: day_per_month = 31; break;
	case 6: day_per_month = 30; break;
	case 7 : day_per_month = 31; break;
	case 8 : day_per_month = 31; break;
	case 9 : day_per_month = 30; break;
	case 10 : day_per_month = 31; break;
	case 11 : day_per_month = 30; break;
	case 12 : day_per_month = 31; break;
	default : std::cout << "Invalid Month Number! Welcome to Earth! We have only 12 Months here! You typed in " << month << endl;
	}

	if (day > day_per_month) {
		std::cout << "Number of day is exceeding number of days allowed for a month on Earth!" << endl;
		return -99999;
	}

	column = (month-1) * day_per_month + day + 4 - 1;  // plus 4 because there are 4 description columns beforehand and minus 1 due to column index starts from 0 in C++
	std::cout << "column number is " << column << endl;

    return column;
}

// Function to prepare vector for average [ high/low temperature / rain / snow / precipation condition]
weather_vector_double_t condition_vector_prepare (weather_data_t weather_record, string station_id, string condition_type, int column) {

	// declare data holding vector
	
	weather_vector_double_t condition_raw;

	// validate input data, i.e. condition type and column number
    if (column == -99999 || ( condition_type.compare("MT") != 0 && condition_type.compare("mint") != 0 && condition_type.compare("rain") != 0 && condition_type.compare("snow") != 0 && condition_type.compare("precip") != 0) ) {
		double error_val = -99999.0;
		condition_raw.push_back(error_val);
		return condition_raw;		
	}

	for (size_t row = 0; row < weather_record.size(); row ++) {  // prepare vector for average high temperature calculation
		// check station ID first
		if (weather_record[row][0] == station_id)
			// check condition column
				if (weather_record[row][3] == condition_type)
					// jump to the date to be processed
                        condition_raw.push_back(atof   (  weather_record[row][column] .c_str()    ));
	}
    //std::cout << "Prepared " << condition_type << " vector is: " << endl;
    //for (size_t i = 0; i < condition_raw.size(); i++)
    //	std::cout << condition_raw[i] << " " ;
	return condition_raw;
}

