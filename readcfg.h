/*
 * readcfg.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#ifndef _READCFG_H_
#define _READCFG_H_

using namespace std;

class ConfigFile {
private:
	string file;
	int multi_string_max;
public:
	ConfigFile(string filename, int max_multi);
	int 	read_int(const string token);
	string 	read_string(const string token);
	string*	read_multi_string(const string token);
									// Einzelne read_*-Methoden um die Tokens einzulesen
	string 	read_MODE();
	int 	read_WAKE_WEEKEND();
	//		read_WAKE();			// Muss ein zweidimensionales Array von Int und dessen Groesse als "Rueckgabewert" besitzen
	//		read_NO_WAKE();			// Muss ein zweidimensionales Array von Int und dessen Groesse als "Rueckgabewert" besitzen
	int 	read_SEND_PACKETS();	// "Packets" vs. "Packages" ?!
	string*	read_MAC();				// Muss ein Array von String und dessen Groesse als "Rueckgabewert" besitzen

};

#endif /* _READCFG_H_ */
