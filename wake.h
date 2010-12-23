/*
 * wake.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */
#include <string>
#include "readcfg.h"

#ifndef _WAKE_H_
#define _WAKE_H_

using namespace std;

class Wake {
private:
	string MODE;
	bool WAKE_WEEKEND;
	int** WAKE;
	int** NO_WAKE;
	int SEND_PACKETS;
	string* MAC;
public:
	void wake_it(ConfigFile& cfg);
	void read_config(ConfigFile& cfg);
	bool check_weekend();
	bool check_date(int** date);
	void wake_mac();
};


#endif /* _WAKE_H_ */
