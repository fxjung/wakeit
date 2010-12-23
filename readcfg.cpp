/*
 * readcfg.cpp
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "readcfg.h"

using namespace std;

ConfigFile::ConfigFile(const string filename) {
	file = filename;
}

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


string ConfigFile::read_MODE() {
	return read_string("MODE");
}

int ConfigFile::read_WAKE_WEEKEND() {
	string input = read_string("WAKE_WEEKEND");
	if (input == "true") return 1;
	else if (input == "false") return 0;
	else return -1;
}

int ConfigFile::read_SEND_PACKETS() {
	return read_int("SEND_PACKETS");
}
