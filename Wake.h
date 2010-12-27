/*
 * Wake.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <string>
#include <ctime>
#include "ConfigFile.h"

#ifndef WAKE_H_
#define WAKE_H_

using namespace std;

class Wake {
private:
// tokens
	string MODE;
	bool VERBOSE;
	bool WAKE_WEEKEND;
	int** WAKE;
	int** NO_WAKE;
	string IP;
	int SEND_PACKETS;
	string* MAC;
// time variables
    time_t timestamp;
    tm *curr_date;
public:
    Wake();
	void wake_it(ConfigFile& cfg);
	void read_config(ConfigFile& cfg);
	bool check_weekend();
	bool check_date(int** date);
	void wake_mac();
};


#endif /* WAKE_H_ */
