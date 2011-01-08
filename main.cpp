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

using namespace std;

/**
 * print usage
 */
void usage() {
  cout << "Aufruf: wakeit [OPTION]..." << endl;
  cout << "Rechner abhängig vom Datum per Wake-on-LAN starten." << endl << endl;
  cout << "  -c [Datei]     Konfigurationsdatei einlesen." << endl;
  cout << "  -l [Datei]     Logdatei spezifizieren." << endl;
  cout << "  -N             Nichts tun, nur simulieren." << endl;
  cout << "      --help     diese Hilfe anzeigen und beenden." << endl;
  cout << "      --version  Versionsinformation anzeigen und beenden." << endl << endl;
  cout << "Standardmäßig wird in /etc/ nach einer Konfigurationsdatei mit dem Namen wakeit.conf gesucht." << endl;
  cout << "Außerdem wird in /var/log/wakeit.log ein Logfile geschrieben." << endl << endl;
  cout << "Melden Sie Programmfehler bitte an <felix.jung@wilhelm-gym.net>" << endl;
  cout << "Homepage: <http://www.wilhelm-gym.net/~felix.jung/wakeit>" << endl;
}

/**
 * print version
 */
void version() {
  cout << "WakeIT 1.0" << endl;
  cout << "Copyright (C) 2010 Felix Jung" << endl;
  cout << "Lizenz GPLv3: GNU GPL Version 3 <http://gnu.org/licenses/gpl.html>" << endl;
  cout << "Dies ist freie Software: Sie können sie ändern und weitergeben." << endl;
  cout << "Es gibt keinerlei Garantien, soweit wie es das Gesetz erlaubt." << endl << endl;
  cout << "Geschrieben von Felix Jung und Roland Hieber." << endl;
}

/**
 * main
 */
int main(int argc, char** argv) {
	// Standard config and log path
	string conffile = "/etc/wakeit.conf";
	string logfile = "/var/log/wakeit.log";
  	bool simulate = false;

  // parse command line parameters
  for(size_t i = 1; i < argc; i++) {
    if(strcmp(argv[i], "--help") == 0) {
      usage();
      return EXIT_SUCCESS;
      cerr << "help" << endl;
    }
    if(strcmp(argv[i], "--version") == 0) {
      version();
      return EXIT_SUCCESS;
    }
    if(strcmp(argv[i], "-c") == 0) {
      if(i+1 > argc-1) {
        // no file given
        usage();
        return EXIT_FAILURE;
      }
      conffile = argv[i+1];
      i++;
    }
    if(strcmp(argv[i], "-l") == 0) {
      if(i+1 > argc-1) {
        // no file given
        usage();
        return EXIT_FAILURE;
      }
      logfile = argv[i+1];
      i++;
    }
    if(strcmp(argv[i], "-N") == 0) {
      simulate = true;
    }
	}

  // test if conffile exists, for nicer error output
  ifstream cf(conffile.c_str());
  if(!cf) {
    cerr << "Datei " << conffile << " konnte nicht geöffnet werden." << endl;
    return EXIT_FAILURE;
  }

  ofstream lf;
  lf.open(logfile.c_str(), ios::app);	// create / open logfile...
  if(!lf) {
    cerr << "Datei " << logfile << " konnte nicht geschrieben werden." << endl;
    return EXIT_FAILURE;
  }

	ConfigFile cfg(conffile, 20); // Initialize config file
	Wake wake(logfile, simulate);
	wake.wake_it(cfg); // Start wake process

	return 0;
}
