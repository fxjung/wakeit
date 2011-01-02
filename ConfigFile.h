/*
 *  ConfigFile.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 *
 *  Copyright (C) 2011 Felix Jung
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
	string file; // Config filename
	int multi_token_max; // Maximal number of equal tokens
public:
	ConfigFile(string filename, int max_multi);
	int 	read_int(const string token);
	string 	read_string(const string token);
	string*	read_multi_string(const string token);
	int**	read_multi_date(const string token);
};

#endif /* CONFIGFILE_H_ */
