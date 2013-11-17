#ifndef CALCULATION_H
#define CALCULATION_H

#include <vector>
#include <sstream>
#include <iostream>
#include "types.h"

int date_data_map (int month, int day);
weather_vector_double_t condition_vector_prepare (weather_data_t weather_record, std::string station_id, std::string condition_type, int column);


#endif
