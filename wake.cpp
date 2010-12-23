/*
 * wake.cpp
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <ctime>
#include "wake.h"
#include "readcfg.h"

using namespace std;

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

void Wake::read_config(ConfigFile& cfg) {
	string weekend = cfg.read_string("WAKE_WEEKEND");
	if (weekend == "true") WAKE_WEEKEND = true;
	if (weekend == "false") WAKE_WEEKEND = false;

	MODE = cfg.read_string("MODE");
	WAKE = cfg.read_multi_date("WAKE");
	NO_WAKE = cfg.read_multi_date("NO_WAKE");
	SEND_PACKETS = cfg.read_int("SEND_PACKETS");
	MAC = cfg.read_multi_string("MAC");
}

bool Wake::check_weekend() {

}

bool Wake::check_date(int** date) {

}

void Wake::wake_mac() {
	string wakestring;
	for(int i = 0; MAC[i] != ""; i++) {
		wakestring = "wakeonlan -i 192.168.255.255 ";
		wakestring.append(MAC[i]);
		wakestring.append(" > /dev/null");
		 for(int j = 0; j < SEND_PACKETS; j++) {
			 system(wakestring.c_str());
		 }
	}
}
