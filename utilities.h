#ifndef UTILITIES_H
#define UTILITIES_H

class weather {
public:

    // constructor
    weather(int);

    // destructor
    ~weather();

	void station_ID_prompt ();
	bool weather_station_ID_check(int);
	bool load_file();


private:
    int test;

};

#endif
