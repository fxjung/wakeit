/*
 * wake.cpp
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include "wake.h"
#include "readcfg.h"

using namespace std;

void Wake::read_config(ConfigFile& cfg) {
	string weekend = cfg.read_string("WAKE_WEEKEND");
	if (weekend == "true") WAKE_WEEKEND = true;
	if (weekend== "false") WAKE_WEEKEND = false;

	MODE = cfg.read_string("MODE");
	WAKE = cfg.read_multi_date("WAKE");
	NO_WAKE = cfg.read_multi_date("NO_WAKE");
	SEND_PACKETS = cfg.read_int("SEND_PACKETS");
	MAC = cfg.read_multi_string("MAC");
}

void Wake::wake_mac() {
	string wakestring;
	for(int i = 0; MAC[i] != ""; i++) {
		wakestring = "wakeonlan -i 192.168.255.255 ";
		wakestring.append(MAC[i]);
		 for(int j = 0; j < SEND_PACKETS; j++) {
			 system(wakestring.c_str());
			 cout << "wakeonlan " << MAC[i] << endl;
		 }
	}
}
