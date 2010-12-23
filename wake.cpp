/*
 * wake.cpp
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include "wake.h"
#include "readcfg.h"

using namespace std;

void read_config(ConfigFile& cfg) {
	string weekend = read_string("WAKE_WEEKEND");
	if (weekend == "true") WAKE_WEEKEND = true;
	if (weekend== "false") WAKE_WEEKEND = false;

	MODE = cfg.read_string("MODE");
	WAKE = cfg.read_multi_date("WAKE");
	NO_WAKE = cfg.read_multi_date("NO_WAKE");
	SEND_PACKETS = cfg.read_int("SEND_PACKETS");
	MAC = cfg.read_multi_string("MAC");
}

void Wake::wake_mac() {

	for(int i = 0; mac[i] != ""; i++) {
		 for(int j = 0; j < packets; j++) {
			 cout << "wakeonlan " << mac[i] << endl;
		 }
	}
}
