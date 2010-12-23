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
	multi_token_max = max_multi;
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
	string* multi_string = new string[multi_token_max];
	for(int i = 0; i < multi_token_max; i++) multi_string[i] = "";
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
   		if(first == token && atoi(number.c_str()) > -1 && atoi(number.c_str()) < multi_token_max) multi_string[atoi(number.c_str())] = content;
 	}
 	return multi_string;
}

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

	for (int i = 0; !config.eof(); i++) {
    	char buf[100] = {0};
    	string first;
    	string number;
   		string second;
    	string content[6];
    	string third;

    	config.getline(buf, sizeof(buf));
    	istringstream istr(string(buf), ios_base::out);
    	istr >> first >> number >> second >> content[0] >> content[1] >> content[2] >> third >> content[3] >> content[4] >> content[5];
   		if(first == token && atoi(number.c_str()) > -1 && atoi(number.c_str()) < multi_token_max) {
   			for(int j = 0; j < 6; j++) {
   				multi_date[atoi(number.c_str())][j] = atoi(content[j].c_str());
   			}
   		}
 	}
 	return multi_date;
}
