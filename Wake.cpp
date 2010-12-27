/*
 * Wake.cpp
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <ctime>
#include "Wake.h"
#include "ConfigFile.h"

using namespace std;

Wake::Wake() {
	// Initialize time
    timestamp = time(0);
    curr_date = localtime(&timestamp);
}

// Process the different parameters
void Wake::wake_it(ConfigFile& cfg) {
	read_config(cfg);
	if(MODE == "always") {wake_mac(); return;}
	if(MODE == "never") return;
	if(MODE == "normal") {
		if(check_date(WAKE)) {wake_mac(); return;}
		if(check_date(NO_WAKE)) return;
		if(WAKE_WEEKEND && check_weekend()) {wake_mac(); return;}
		if(!WAKE_WEEKEND && check_weekend()) return;
		wake_mac();
	}
}

// Read the tokens and save their values in the corresponding variables
// Define standard values
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

// Check whether the current date is at weekend
bool Wake::check_weekend() {
    if(curr_date->tm_wday == 0 || curr_date->tm_wday == 6) return true;
    return false;
}

// Check whether the current date is between the dates mentioned in the config
bool Wake::check_date(int** date) {
	for(int i = 0; date[i][0] != 0; i++) {

/*		// For testing date output
		for(int j = 0; j < 6; j++) {
			cout << date[i][j] << " ";
		}
		cout << endl;
*/

/*		// Old, buggy algorithm. Kept just for fun ;-)
		if(date[i][2] < (curr_date->tm_year + 1900) && date[i][5] > (curr_date->tm_year + 1900)) return true;
		if(date[i][2] == (curr_date->tm_year + 1900)) {
			if(date[i][1] < (curr_date->tm_mon + 1) && date[i][4] > (curr_date->tm_mon + 1)) return true;
			if(date[i][1] == (curr_date->tm_mon + 1)) {
				if(date[i][0] <= curr_date->tm_mday && date[i][3] >= curr_date->tm_mday) return true;
			}
		}
		else if(date[i][5] == (curr_date->tm_year + 1900)) {
			if(date[i][4] > (curr_date->tm_mon + 1)) return true;
			if(date[i][4] == (curr_date->tm_mon + 1)) {
				if(date[i][3] >= curr_date->tm_mday) return true;
			}
		}
	}
*/

		// New algorithm, should work correctly
		if(date[i][2] < (curr_date->tm_year + 1900) && date[i][5] > (curr_date->tm_year + 1900)) return true;
		if(date[i][2] == (curr_date->tm_year + 1900) && date[i][5] == (curr_date->tm_year + 1900)) {
			if(date[i][1] < (curr_date->tm_mon + 1) && date[i][4] > (curr_date->tm_mon + 1)) return true;
			if(date[i][1] == (curr_date->tm_mon + 1) && date[i][4] == (curr_date->tm_mon + 1)) {
				if(date[i][0] <= curr_date->tm_mday && date[i][3] >= curr_date->tm_mday) return true;
			}
			else if(date[i][1] < (curr_date->tm_mon + 1) && date[i][4] == (curr_date->tm_mon + 1)) {
				if(date[i][3] >= (curr_date->tm_mday)) return true;
			}
			else if(date[i][1] == (curr_date->tm_mon + 1) && date[i][4] > (curr_date->tm_mon + 1)) {
				if(date[i][0] <= (curr_date->tm_mday)) return true;
			}
		}
		else if(date[i][2] < (curr_date->tm_year + 1900) && date[i][5] == (curr_date->tm_year + 1900)) {
			if(date[i][4] > (curr_date->tm_mon + 1)) return true;
			if(date[i][4] == (curr_date->tm_mon + 1)) {
				if(date[i][3] >= (curr_date->tm_mday)) return true;
			}
		}
		else if(date[i][2] == (curr_date->tm_year + 1900) && date[i][5] > (curr_date->tm_year + 1900)) {
			if(date[i][1] < (curr_date->tm_mon + 1)) return true;
			if(date[i][1] == (curr_date->tm_mon + 1)) {
				if(date[i][0] <= (curr_date->tm_mday)) return true;
			}
		}
	}
	return false;
}

void Wake::wake_mac() {
	string wakestring;
	for(int i = 0; MAC[i] != ""; i++) { // For every MAC do...
		wakestring = "wakeonlan -i ";	// Wake-on-LAN command; TODO: though static - should be replaced by a user configurable string
		wakestring.append(IP);			// Append IP-Space
		wakestring.append(" ");
		wakestring.append(MAC[i]);		// Append MAC
		if(!VERBOSE) wakestring.append(" > /dev/null"); // Verbose? If not, put the output into /dev/null
		for(int j = 0; j < SEND_PACKETS; j++) { // If set, send more than one packet
			 system(wakestring.c_str());
		}
	}
}
