/*
 *  ConfigFile.cpp
 *
 *  Created on: 23.12.2010
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

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "ConfigFile.h"

using namespace std;

ConfigFile::ConfigFile(const string filename, int max_multi) {
	file = filename;
	multi_token_max = max_multi;
}

// Read single integer
int ConfigFile::read_int(const string token) {
	ifstream config(file.c_str());
	if(!config) {cout << "Error: Cannot open file " << file << endl; return -1;}

	while(!config.eof()) {
    	char buf[100] = {0};
    	string first;
   		string second;
    	string content;

    	config.getline(buf, sizeof(buf));
    	istringstream istr(string(buf), ios_base::out);
    	istr >> first >> second >> content;
   		if(first == token) return atoi(content.c_str());
 	}
 	return -1;
}

// Read single string
string ConfigFile::read_string(const string token) {
	ifstream config(file.c_str());
	if(!config) {cout << "Error: Cannot open file " << file << endl; return "";}

	while(!config.eof()) {
    	char buf[100] = {0};
    	string first;
   		string second;
    	string content;

    	config.getline(buf, sizeof(buf));
    	istringstream istr(string(buf), ios_base::out);
    	istr >> first >> second >> content;
   		if(first == token) return content;
 	}
 	return "";
}

// Read multiple strings (--> MAC input)
string* ConfigFile::read_multi_string(const string token) {
	ifstream config(file.c_str());
	string* multi_string = new string[multi_token_max];
	for(int i = 0; i < multi_token_max; i++) multi_string[i] = "";
	if(!config) {cout << "Error: Cannot open file " << file << endl; return multi_string;}
	int number = 0;

	for (int i = 0; !config.eof(); i++) {
    	char buf[100] = {0};
    	string first;
   		string second;
    	string content;

    	config.getline(buf, sizeof(buf));
    	istringstream istr(string(buf), ios_base::out);
    	istr >> first >> second >> content;
   		if(first == token && number < multi_token_max) {multi_string[number] = content; number++;}
 	}
 	return multi_string;
}

// Read multiple integer values as a date
int** ConfigFile::read_multi_date(const string token) {
	ifstream config(file.c_str());
	int** multi_date = new int*[multi_token_max];
	for(int i = 0; i < multi_token_max; i++) multi_date[i] = new int[6];
	for(int i = 0; i < multi_token_max; i++) {
		for(int j = 0; j < 6; j++) {
			multi_date[i][j] = 0;
		}
	}
	if(!config) {cout << "Error: Cannot open file " << file << endl; return multi_date;}
	int number = 0;

	for (int i = 0; !config.eof(); i++) {
    	char buf[100] = {0};
    	string first;
   		string second;
    	string content[6];
    	string third;

    	config.getline(buf, sizeof(buf));
    	istringstream istr(string(buf), ios_base::out);
    	istr >> first >> second >> content[0] >> content[1] >> content[2] >> third >> content[3] >> content[4] >> content[5];
   		if(first == token && number < multi_token_max) {
   			for(int j = 0; j < 6; j++) {
   				multi_date[number][j] = atoi(content[j].c_str());
   			}
   			number++;
   		}
 	}
 	return multi_date;
}
