/*
 *  Wake.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 *
 *  Copyright (C) 2011 Felix Jung
 *
 *  This file is part of WakeIT.
 *
 *  WakeIT is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  WakeIT is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with WakeIT.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <ctime>
#include "ConfigFile.h"

#ifndef WAKE_H_
#define WAKE_H_

using namespace std;

class Wake {
private:
	string logfile; // logfile name
	bool SIMULATE;

	// tokens
	string MODE;
	bool VERBOSE;
	bool WAKE_WEEKEND;
	int** WAKE;
	int** NO_WAKE;
	string IP;
	int SEND_PACKETS;
	string* MAC;

	// Time variables
    time_t timestamp;
    tm *curr_date;
public:
    Wake(string filename, bool simulate = false);
	void wake_it(ConfigFile& cfg);
	void read_config(ConfigFile& cfg);
	bool check_weekend();
	bool is_after_start(int** date);
	bool is_before_end(int** date);
	void wake_mac();
};


#endif /* WAKE_H_ */
