/*
 * readcfg.cpp
 *
 *  Created on: 22.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <iostream>
#include "readcfg.h"
#include "wake.h"

void print_time();

int main(int argc, char** argv) {
	ConfigFile cfg("wakeit.ini", 20);
	Wake wake;
	wake.wake_it(cfg);


/*
	int** wake = cfg.read_WAKE();
		for(int i = 0; wake[i][0] != 0; i++) {		// Nur so lange das Array ausgeben, bis der Inhalt eines Strings "" lautet, also keine weiteren MACs vorhanden sind.
			for(int j = 0; j < 6; j++) {
				cout << wake[i][j] << endl;
			}
	}

*/
}
