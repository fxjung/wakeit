/*
 *  Wake.cpp
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

#include <ctime>
#include "Wake.h"
#include "ConfigFile.h"

using namespace std;

Wake::Wake(string filename, bool simulate) : logfile(filename), SIMULATE(simulate) {
  // initialize time
  timestamp = time(0);
  curr_date = localtime(&timestamp);
}

// process the different parameters
void Wake::wake_it(ConfigFile& cfg) {
	read_config(cfg);
	if(MODE == "always") {wake_mac(); return;}
	if(MODE == "never") return;
	if(MODE == "normal") {
		// for each found token check whether date is between start and end 
		for(int i = 0; WAKE[i][0] != 0; i++) {
			if(is_after_start(WAKE, i) && is_before_end(WAKE, i)) {wake_mac(); return;}
		}
		// the same for "NO_WAKE"
		for(int i = 0; NO_WAKE[i][0] != 0; i++) {
			if(is_after_start(NO_WAKE, i) && is_before_end(NO_WAKE, i)) return;
		}
		
		if(WAKE_WEEKEND && check_weekend()) {wake_mac(); return;}
		if(!WAKE_WEEKEND && check_weekend()) return;
		wake_mac();
	}
}

// read the tokens and save their values in the corresponding variables
// define standard values
void Wake::read_config(ConfigFile& cfg) {
	if (cfg.read_string("VERBOSE") == "true") VERBOSE = true;
	else VERBOSE = false;

	if (cfg.read_string("WAKE_WEEKEND") == "true") WAKE_WEEKEND = true;
	else WAKE_WEEKEND = false;

	MODE = cfg.read_string("MODE");
	if(MODE == "") MODE.append("normal");

	WAKE = cfg.read_multi_date("WAKE");
	NO_WAKE = cfg.read_multi_date("NO_WAKE");

	IP = cfg.read_string("IP");
	if(IP == "") IP.append("255.255.255.255");

	SEND_PACKETS = cfg.read_int("SEND_PACKETS");
	if(SEND_PACKETS == -1) SEND_PACKETS = 1;

	MAC = cfg.read_multi_string("MAC");
}

// check whether the current date is at weekend
bool Wake::check_weekend() {
    if(curr_date->tm_wday == 0 || curr_date->tm_wday == 6) return true;
    return false;
}

// check whether the current date is after start
bool Wake::is_after_start(int** date, int i) {
	if(date[i][2] < (curr_date->tm_year + 1900)) return true;
	if(date[i][2] == (curr_date->tm_year + 1900)) {
		if(date[i][1] < (curr_date->tm_mon + 1)) return true;
		if(date[i][1] == (curr_date->tm_mon + 1)) {
			if(date[i][0] <= curr_date->tm_mday) return true;
		}
	}
	return false;
}

// check whether the current date is before end
bool Wake::is_before_end(int** date, int i) {
	if(date[i][5] > (curr_date->tm_year + 1900)) return true;
	if(date[i][5] == (curr_date->tm_year + 1900)) {
		if(date[i][4] > (curr_date->tm_mon + 1)) return true;
		if(date[i][4] == (curr_date->tm_mon + 1)) {
			if(date[i][3] >= curr_date->tm_mday) return true;
		}
	}
	return false;
}

void Wake::wake_mac() {
	string wakestring;

	ofstream log;
	log.open(logfile.c_str(), ios::app);
	// write timestamp
	log << curr_date->tm_hour << ':' << curr_date->tm_min << ':' << curr_date->tm_sec << '\t' << curr_date->tm_mday << '-' << curr_date->tm_mon+1 << '-' << curr_date->tm_year+1900 << "\tWake up ";
	// log whether simulation is enabled
	if(SIMULATE) log << "simulated\t";
	else log << "\t\t";

	for(int i = 0; MAC[i] != ""; i++) { // for every MAC do...
		wakestring = "wakeonlan -i ";	// wake-on-LAN command; TODO: though static - should be replaced by a user configurable string
		wakestring.append(IP);			// append IP-Space
		wakestring.append(" ");
		wakestring.append(MAC[i]);		// append MAC
		if(!VERBOSE) wakestring.append(" > /dev/null"); // verbose? If not, put the output into /dev/null
		for(int j = 0; j < SEND_PACKETS; j++) { // SEND_PACKETS: if set, send more than one packet
			if(SIMULATE) cout << wakestring << endl;
			else system(wakestring.c_str());
		}
		log << MAC[i] << '\t';
	}
	log << endl;
}
