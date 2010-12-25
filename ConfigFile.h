/*
 * ConfigFile.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

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
};

#endif /* CONFIGFILE_H_ */
