/*
 * readcfg.cpp
 *
 *  Created on: 22.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <iostream>
#include <cstring>
#include "readcfg.h"
#include "wake.h"

int main(int argc, char** argv) {
	string file = "/etc/wakeit/wakeit.conf";
	if(argc == 2 && !strcmp(argv[1], "--help")) {
		cout << "Aufruf: wakeit [OPTION] [DATEI]" << endl;
		cout << "Rechner abhaengig vom Datum per Wake-on-LAN starten." << endl << endl;
		cout << "  -c [Datei]                       Konfigurationsdatei einlesen" << endl;
		cout << "      --help     diese Hilfe anzeigen und beenden" << endl;
		cout << "      --version  Versionsinformation anzeigen und beenden" << endl << endl;
		cout << "Standardmäßig wird in /etc/wakeit nach einer Konfigurationsdatei mit dem Namen wakeit.conf gesucht." << endl << endl;
		cout << "Melden Sie Programmfehler bitte an <felix.jung@wilhelm-gym.net>" << endl;
		cout << "Homepage: <http://www.wilhelm-gym.net/~felix.jung/wakeit>" << endl;
		return 0;

	}
	if(argc == 2 && !strcmp(argv[1], "--version")) {
		cout << "WakeIT 1.0 beta" << endl;
		cout << "Copyright © 2010 Felix Jung" << endl;
		cout << "Lizenz GPLv3+: GNU GPL Version 3 oder höher <http://gnu.org/licenses/gpl.html>" << endl;
		cout << "Dies ist freie Software: Sie können sie ändern und weitergeben." << endl;
		cout << "Es gibt keinerlei Garantien, soweit wie es das Gesetz erlaubt." << endl << endl;
		cout << "Geschrieben von Felix Jung." << endl;
		return 0;

	}
	if(argc == 2 && argv[1][1] != '-') {
		file = argv[1];
	}


	ConfigFile cfg(file, 20);
	Wake wake;
	wake.wake_it(cfg);

	return 0;
}
