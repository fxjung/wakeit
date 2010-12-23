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
	int multi_token_max;
public:
	ConfigFile(string filename, int max_multi);
	int 	read_int(const string token);
	string 	read_string(const string token);
	string*	read_multi_string(const string token);
	int**	read_multi_date(const string token);
	// Einzelne read_*-Methoden um die Tokens einzulesen
	string 	read_MODE();
	int 	read_WAKE_WEEKEND();
	int**	read_WAKE();
	int**	read_NO_WAKE();
	int 	read_SEND_PACKETS();	// "Packets" vs. "Packages" ?!
	string*	read_MAC();

};

#endif /* _READCFG_H_ */
