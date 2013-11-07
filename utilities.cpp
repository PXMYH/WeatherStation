#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include "utilities.h"

using namespace std;

// declaring constants
const int NUM_DATA_ENTRY = 300000;


struct weather_entry {
    int station_ID;
    string station_name;
    int operation_year;
    string weather_type;
    vector<int> weather_data;
};


weather :: weather (int val) {
    test = val;
	cout << "test value is => " << test << endl;
}

weather :: ~weather() {
    test = 0;
}

void weather::station_ID_prompt () {
    int station_ID;
    cout << "Please type in weather station ID for detailed report: " << station_ID << endl;
}

bool weather::weather_station_ID_check (int station_ID) {
	return true;
}

//istream& operator >> (istream &is, weather_entry &entry)
//{
//  char delim;
//  is >> entry.station_ID
//     >> delim
//     >> entry.station_name
//     >> delim
//     >> entry.operation_year
//     >> delim
//     >> entry.weather_type
//     >> delim
//     >> entry.weather_data;

//  return is;
//}

//ostream& operator << (ostream &os, const weather_entry &entry)
//{
//  os << entry.station_ID
//     << ','
//     << entry.station_name
//     << ','
//     << entry.operation_year
//     << ','
//     << entry.weather_type
//     << ','
//     << entry.weather_data<int>;
//
//  return os;
//}

bool weather::load_file () {
    // locate weather source data CSV file
    string weather_data_src = "BCnorthWeatherData.csv";

    // open weather source data
    ifstream file_handle(weather_data_src.c_str());
    if (!file_handle)
        //error ("Can't open weather data source file ", weather_data_src);
			return false;

    // load data into pre-defined structure
    cout << "LOADING DATA ..." << endl;
    vector<weather_entry> weather_data_entries (NUM_DATA_ENTRY);
    string line;

    // read CSV file line by line and parse into pre-defined structure vector
    while (getline(file_handle, line)) {
        weather_entry data_row;
        stringstream linestr(line);
        //linestr >> data_row;
        weather_data_entries.push_back(data_row);

        //cout << data_row << endl;
    }
    cout << "DATA LOADED." << endl;

    // close weather source data
    // this could be implicitly closed when we are leaving the scope of "load_file" function
    file_handle.close();
}
