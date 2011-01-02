/*
 * main.cpp
 *
 *  Created on: 22.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
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
  cout << "Aufruf: wakeit [OPTION]" << endl;
  cout << "Rechner abhängig vom Datum per Wake-on-LAN starten." << endl << endl;
  cout << "  -c [Datei]                       Konfigurationsdatei einlesen" << endl;
  cout << "      --help     diese Hilfe anzeigen und beenden" << endl;
  cout << "      --version  Versionsinformation anzeigen und beenden" << endl;
  cout << "  -N             Nichts tun, nur simulieren." << endl << endl;
  cout << "Standardmäßig wird in /etc/wakeit nach einer Konfigurationsdatei mit dem Namen wakeit.conf gesucht." << endl << endl;
  cout << "Melden Sie Programmfehler bitte an <felix.jung@wilhelm-gym.net>" << endl;
  cout << "Homepage: <http://www.wilhelm-gym.net/~felix.jung/wakeit>" << endl;
}

/**
 * print version
 */
void version() {
  cout << "WakeIT 1.0 beta" << endl;
  cout << "Copyright © 2010 Felix Jung" << endl;
  cout << "Lizenz GPLv3+: GNU GPL Version 3 oder höher <http://gnu.org/licenses/gpl.html>" << endl;
  cout << "Dies ist freie Software: Sie können sie ändern und weitergeben." << endl;
  cout << "Es gibt keinerlei Garantien, soweit wie es das Gesetz erlaubt." << endl << endl;
  cout << "Geschrieben von Felix Jung." << endl;
}

/**
 * main
 */
int main(int argc, char** argv) {
	string file = "/etc/wakeit/wakeit.conf";
  bool simulate = false;

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
      file = argv[i+1];
      i++;
    }
    if(strcmp(argv[i], "-N") == 0) {
      simulate = true;
    }
	}

	ConfigFile cfg(file, 20);
	Wake wake(simulate);
	wake.wake_it(cfg);

	return 0;
}
