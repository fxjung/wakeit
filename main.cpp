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
	ConfigFile cfg("wakeit.ini", 20);

	string* mac = cfg.read_MAC();
	for(int i = 0; mac[i] != ""; i++) {		// Nur so lange das Array ausgeben, bis der Inhalt eines Strings "" lautet, also keine weiteren MACs vorhanden sind.
		cout << mac[i] << endl;
	}

	int** wake = cfg.read_WAKE();
		for(int i = 0; wake[i][0] != 0; i++) {		// Nur so lange das Array ausgeben, bis der Inhalt eines Strings "" lautet, also keine weiteren MACs vorhanden sind.
			for(int j = 0; j < 6; j++) {
				cout << wake[i][j] << endl;
			}
	}

	int** no_wake = cfg.read_NO_WAKE();
		for(int i = 0; no_wake[i][0] != 0; i++) {		// Nur so lange das Array ausgeben, bis der Inhalt eines Strings "" lautet, also keine weiteren MACs vorhanden sind.
			for(int j = 0; j < 6; j++) {
				cout << no_wake[i][j] << endl;
			}
	}

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
