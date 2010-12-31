/*
 * 	main.cpp
 *
 *  Created on: 22.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 *
 *	Copyright (C) 2011 Felix Jung
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

#include <iostream>
#include <cstring>
#include "ConfigFile.h"
#include "Wake.h"

int main(int argc, char** argv) {
	// Standard config path
	string file = "/etc/wakeit/wakeit.conf";

	// Print program help
	if(argc == 2 && !strcmp(argv[1], "--help")) {
		cout << "Aufruf: wakeit [OPTION]" << endl;
		cout << "Rechner abhaengig vom Datum per Wake-on-LAN starten." << endl << endl;
		cout << "  -c [Datei      Konfigurationsdatei einlesen" << endl;
		cout << "  --help     diese Hilfe anzeigen und beenden" << endl;
		cout << "  --version  Versionsinformation anzeigen und beenden" << endl << endl;
		cout << "Standardmäßig wird in /etc/wakeit nach einer Konfigurationsdatei mit dem Namen wakeit.conf gesucht." << endl << endl;
		cout << "Melden Sie Programmfehler bitte an <felix.jung@wilhelm-gym.net>" << endl;
		cout << "Homepage: <http://www.wilhelm-gym.net/~felix.jung/wakeit>" << endl;
		return 0;
	}

	// Print version info
	if(argc == 2 && !strcmp(argv[1], "--version")) {
		cout << "WakeIT 1.0" << endl;
		cout << "Copyright (C) 2011 Felix Jung" << endl;
		cout << "Lizenz GPLv3: GNU GPL Version 3 <http://gnu.org/licenses/gpl.html>" << endl;
		cout << "Dies ist freie Software: Sie können sie ändern und weitergeben." << endl;
		cout << "Es gibt keinerlei Garantien, soweit wie es das Gesetz erlaubt." << endl << endl;
		cout << "Geschrieben von Felix Jung." << endl;
		return 0;
	}

	// Read in config filename
	if(argc == 3 && !strcmp(argv[1], "-c")) {
		file = argv[2];
	}

	ConfigFile cfg(file, 20); // Initialize config file
	Wake wake;
	wake.wake_it(cfg); // Start wake process

	return 0;
}
