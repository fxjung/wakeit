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

ConfigFile::ConfigFile(const string filename, int max_multi) {
	file = filename;
	multi_string_max = max_multi;
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

string* ConfigFile::read_multi_string(const string token) {
	ifstream config(file.c_str());
	string* multi_string = new string[multi_string_max];
	for(int i = 0; i < multi_string_max; i++) multi_string[i] = "";
	if(!config) {cout << "Error: Cannot open file " << file << endl; return multi_string;}

	for (int i = 0; !config.eof(); i++) {
    	char buf[100] = {0};
    	string first;
    	string number;
   		string second;
    	string content;

    	config.getline(buf, sizeof(buf));
    	istringstream istr(string(buf), ios_base::out);
    	istr >> first >> number >> second >> content;
   		if(first == token && atoi(number.c_str()) > -1 && atoi(number.c_str()) < multi_string_max) multi_string[atoi(number.c_str())] = content;
 	}
 	return multi_string;
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

string* ConfigFile::read_MAC() {
	return read_multi_string("MAC");
}
