/*
 * readcfg.cpp
 *
 *  Created on: 22.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <iostream>
#include <ctime>
#include "readcfg.h"

void print_time();

int main(int argc, char** argv) {
	ConfigFile cfg("wakeit.ini");



	cout << cfg.read_WAKE_WEEKEND() << endl;
	cout << cfg.read_MODE() << endl;
	cout << cfg.read_SEND_PACKETS() << endl;
}






void print_time() {
    time_t Zeitstempel;
    tm *nun;
    Zeitstempel = time(0);
    nun = localtime(&Zeitstempel);
    cout << nun->tm_mday << '.' << nun->tm_mon+1 << '.' << nun->tm_year+1900 << " - " << nun->tm_hour << ':' << nun->tm_min << endl;
}
