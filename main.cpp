#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;


class ConfigFile {
  private:
	string file;
	
  public:
	ConfigFile(string filename);
	int read_int(const string token);
	string read_string(const string token);
};

void print_time();

int main(int argc, char** argv) {
	ConfigFile cfg("config.cfg");
	cout << cfg.read_int("foo") << endl;
	cout << "wakeonlan " << cfg.read_string("MAC") << endl;
	print_time();
}


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

void print_time() {
    time_t Zeitstempel;
    tm *nun;
    Zeitstempel = time(0);
    nun = localtime(&Zeitstempel);
    cout << nun->tm_mday << '.' << nun->tm_mon+1 << '.' << nun->tm_year+1900 << " - " << nun->tm_hour << ':' << nun->tm_min << endl;
}